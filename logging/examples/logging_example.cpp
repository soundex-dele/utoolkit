#include "utoolkit/logging/logger.h"
#include <thread>
#include <chrono>

int main() {
    // Initialize logging system
    utoolkit::logging::Logger::GetInstance().Initialize("example_logger", "[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [%t] %v", spdlog::level::trace);

    // Log messages with different levels
    UTOOLKIT_LOG_TRACE("This is a trace message");
    UTOOLKIT_LOG_DEBUG("This is a debug message");
    UTOOLKIT_LOG_INFO("This is an info message");
    UTOOLKIT_LOG_WARN("This is a warning message");
    UTOOLKIT_LOG_ERROR("This is an error message");
    UTOOLKIT_LOG_CRITICAL("This is a critical message");

    // Use format string
    int value = 42;
    std::string text = "example text";
    UTOOLKIT_LOG_INFO("Format example - value: {}, text: {}", value, text);

    // Log from different thread
    std::thread worker([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        UTOOLKIT_LOG_INFO("This message comes from worker thread");
    });

    // Dynamically change log level
    UTOOLKIT_LOG_DEBUG("Debug message is visible now");
    utoolkit::logging::Logger::GetInstance().SetLevel(spdlog::level::info);
    UTOOLKIT_LOG_DEBUG("This debug message will not show");
    UTOOLKIT_LOG_INFO("But info message is still visible");

    worker.join();
    return 0;
}