#include <utoolkit/logging/logger.h>
#include <iostream>

using namespace utoolkit::logging;

int main() {
    std::cout << "=== Logger Example ===" << std::endl;
    
    Logger& logger = Logger::instance();
    logger.set_log_level(LogLevel::DEBUG);
    
    UT_TRACE("This is a trace message");
    UT_DEBUG("This is a debug message");
    UT_INFO("This is an info message");
    UT_WARN("This is a warning message");
    UT_ERROR("This is an error message");
    UT_FATAL("This is a fatal message");
    
    logger.set_log_file("example.log");
    UT_INFO("This message will be written to file");
    
    std::cout << "Log messages have been written to example.log" << std::endl;
    
    return 0;
}