#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>

namespace utoolkit {
namespace threadpool {

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();
    
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::invoke_result_t<F, Args...>>;
    
    size_t get_thread_count() const;
    size_t get_task_count() const;
    
    void shutdown();
    bool is_shutdown() const;

private:
    mutable std::mutex queue_mutex_;
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    
    std::condition_variable condition_;
    bool stop_;
    size_t thread_count_;
    
    void worker_thread();
};

// Implementation of enqueue method
template<typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::invoke_result_t<F, Args...>> {
    
    using return_type = typename std::invoke_result_t<F, Args...>;
    
    auto task = std::make_shared<std::packaged_task<return_type()>> (
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    
    std::future<return_type> result = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        
        if (stop_) {
            throw std::runtime_error("ThreadPool is stopped");
        }
        
        tasks_.emplace([task]() { (*task)(); });
    }
    condition_.notify_one();
    return result;
}

} // namespace threadpool
} // namespace utoolkit