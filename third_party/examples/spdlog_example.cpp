#include <iostream>
#include <memory>

// 如果spdlog可用，包含头文件
#ifdef HAVE_SPDLOG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#endif

int main() {
#ifdef HAVE_SPDLOG
    try {
        // 基本控制台日志
        spdlog::info("Welcome to spdlog!");
        spdlog::error("Some error message with arg: {}", 1);
        
        // 不同级别的日志
        spdlog::warn("Easy padding in numbers like {:08d}", 12);
        spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        
        // 文件日志
        auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
        file_logger->info("This message will be written to file");
        
        // 设置日志级别
        spdlog::set_level(spdlog::level::debug);
        spdlog::debug("This message should be displayed..");
        
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
#else
    std::cout << "spdlog library not available" << std::endl;
#endif
    return 0;
}