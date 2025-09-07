#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <mutex>
#include <chrono>

namespace utoolkit {
namespace logging {

enum class LogLevel {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

class Logger {
public:
    static Logger& instance();
    
    void set_log_level(LogLevel level);
    void set_log_file(const std::string& filename);
    void enable_console_output(bool enable);
    
    void log(LogLevel level, const std::string& message, 
             const std::string& file = "", int line = 0);
    
    void trace(const std::string& message, const std::string& file = "", int line = 0);
    void debug(const std::string& message, const std::string& file = "", int line = 0);
    void info(const std::string& message, const std::string& file = "", int line = 0);
    void warn(const std::string& message, const std::string& file = "", int line = 0);
    void error(const std::string& message, const std::string& file = "", int line = 0);
    void fatal(const std::string& message, const std::string& file = "", int line = 0);

private:
    Logger();
    ~Logger();
    
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    std::string level_to_string(LogLevel level);
    std::string get_current_time();
    
    LogLevel current_level_;
    std::ofstream log_file_;
    std::mutex mutex_;
    bool console_output_enabled_;
};

#define UT_TRACE(msg) utoolkit::logging::Logger::instance().trace(msg, __FILE__, __LINE__)
#define UT_DEBUG(msg) utoolkit::logging::Logger::instance().debug(msg, __FILE__, __LINE__)
#define UT_INFO(msg) utoolkit::logging::Logger::instance().info(msg, __FILE__, __LINE__)
#define UT_WARN(msg) utoolkit::logging::Logger::instance().warn(msg, __FILE__, __LINE__)
#define UT_ERROR(msg) utoolkit::logging::Logger::instance().error(msg, __FILE__, __LINE__)
#define UT_FATAL(msg) utoolkit::logging::Logger::instance().fatal(msg, __FILE__, __LINE__)

} // namespace logging
} // namespace utoolkit