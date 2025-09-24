#include <utoolkit/logging/logger.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

namespace utoolkit {
namespace logging {

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : current_level_(LogLevel::INFO), console_output_enabled_(true) {
}

Logger::~Logger() {
    if (log_file_.is_open()) {
        log_file_.close();
    }
}

void Logger::set_log_level(LogLevel level) {
    current_level_ = level;
}

void Logger::set_log_file(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (log_file_.is_open()) {
        log_file_.close();
    }
    
    log_file_.open(filename, std::ios::app);
    if (!log_file_.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

void Logger::enable_console_output(bool enable) {
    console_output_enabled_ = enable;
}

void Logger::log(LogLevel level, const std::string& message, 
                 const std::string& file, int line) {
    if (level < current_level_) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::string log_entry = get_current_time() + " [" + level_to_string(level) + "] " + message;
    
    if (!file.empty()) {
        log_entry += " (" + file;
        if (line > 0) {
            log_entry += ":" + std::to_string(line);
        }
        log_entry += ")";
    }
    
    if (console_output_enabled_) {
        std::cout << log_entry << std::endl;
    }
    
    if (log_file_.is_open()) {
        log_file_ << log_entry << std::endl;
        log_file_.flush();
    }
}

void Logger::trace(const std::string& message, const std::string& file, int line) {
    log(LogLevel::TRACE, message, file, line);
}

void Logger::debug(const std::string& message, const std::string& file, int line) {
    log(LogLevel::DEBUG, message, file, line);
}

void Logger::info(const std::string& message, const std::string& file, int line) {
    log(LogLevel::INFO, message, file, line);
}

void Logger::warn(const std::string& message, const std::string& file, int line) {
    log(LogLevel::WARN, message, file, line);
}

void Logger::error(const std::string& message, const std::string& file, int line) {
    log(LogLevel::ERROR, message, file, line);
}

void Logger::fatal(const std::string& message, const std::string& file, int line) {
    log(LogLevel::FATAL, message, file, line);
}

std::string Logger::level_to_string(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

std::string Logger::get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();
    
    return ss.str();
}

} // namespace logging
} // namespace utoolkit