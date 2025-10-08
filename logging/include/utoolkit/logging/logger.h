#pragma once

#ifndef UTOOLKIT_LOGGING_LOGGER_H
#define UTOOLKIT_LOGGING_LOGGER_H

#include <memory>
#include <string>

namespace utoolkit {
namespace logging {
enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Critical,
};

class Logger {
public:
    static Logger& GetInstance();
    void Initialize(const std::string& logger_name = "utoolkit_logger",
                   const std::string& pattern = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [%t] %v",
                   LogLevel level = LogLevel::Info);

    void SetLevel(LogLevel level);
    LogLevel GetLevel() const;

    void Trace(const char* msg);

    void Debug(const char* msg);

    void Info(const char* msg);

    void Warn(const char* msg);

    void Error(const char* msg);

    void Critical(const char* msg);

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    class Impl;
    std::shared_ptr<Impl> impl_;
};

} // namespace logging
} // namespace utoolkit

#endif // UTOOLKIT_LOGGING_LOGGER_H