#include <utoolkit/threadpool/threadpool.h>
#include <utoolkit/utils/time_utils.h>
#include <iostream>
#include <vector>
#include <chrono>

using namespace utoolkit::threadpool;
using namespace utoolkit::utils;

int main() {
    std::cout << "=== ThreadPool Example ===" << std::endl;
    
    ThreadPool pool(4);
    std::cout << "Created thread pool with " << pool.get_thread_count() << " threads" << std::endl;
    
    TimeUtils::Timer timer;
    timer.start();
    
    std::vector<std::future<int>> results;
    
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(
            pool.enqueue([i]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                return i * i;
            })
        );
    }
    
    std::cout << "Submitted 10 tasks to thread pool" << std::endl;
    
    for (size_t i = 0; i < results.size(); ++i) {
        int result = results[i].get();
        std::cout << "Task " << i << " result: " << result << std::endl;
    }
    
    timer.stop();
    std::cout << "Total execution time: " << timer.elapsed_str() << std::endl;
    
    auto future = pool.enqueue([](int a, int b, int c) {
        return a + b + c;
    }, 10, 20, 30);
    
    std::cout << "Async calculation result: " << future.get() << std::endl;
    
    pool.shutdown();
    
    return 0;
}