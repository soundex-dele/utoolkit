#include <utoolkit/threadpool/threadpool.h>
#include <stdexcept>

namespace utoolkit {
namespace threadpool {

ThreadPool::ThreadPool(size_t num_threads) : stop_(false), thread_count_(num_threads) {
    if (num_threads == 0) {
        thread_count_ = std::thread::hardware_concurrency();
        if (thread_count_ == 0) thread_count_ = 1;
    }
    
    for (size_t i = 0; i < thread_count_; ++i) {
        workers_.emplace_back([this] { worker_thread(); });
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::shutdown() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (stop_) return;
        stop_ = true;
    }
    
    condition_.notify_all();
    
    for (std::thread& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

size_t ThreadPool::get_thread_count() const {
    return thread_count_;
}

size_t ThreadPool::get_task_count() const {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    return tasks_.size();
}

bool ThreadPool::is_shutdown() const {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    return stop_;
}

void ThreadPool::worker_thread() {
    while (true) {
        std::function<void()> task;
        
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            
            condition_.wait(lock, [this] {
                return stop_ || !tasks_.empty();
            });
            
            if (stop_ && tasks_.empty()) {
                return;
            }
            
            task = std::move(tasks_.front());
            tasks_.pop();
        }
        
        task();
    }
}

} // namespace threadpool
} // namespace utoolkit