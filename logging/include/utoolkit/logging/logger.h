#pragma once

#ifndef UTOOLKIT_LOGGING_LOGGER_H
#define UTOOLKIT_LOGGING_LOGGER_H

#include <memory>
#include <string>
#include "spdlog/spdlog.h"

namespace utoolkit {
namespace logging {

class Logger {
public:
    static Logger& GetInstance();

    void Initialize(const std::string& logger_name = "utoolkit_logger",
                   const std::string& pattern = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [%t] %v",
                   spdlog::level::level_enum level = spdlog::level::info);

    void SetLevel(spdlog::level::level_enum level);
    spdlog::level::level_enum GetLevel() const;

    template<typename... Args>
    void Trace(const char* fmt, const Args&... args) {
        logger_->trace(fmt, args...);
    }

    template<typename... Args>
    void Debug(const char* fmt, const Args&... args) {
        logger_->debug(fmt, args...);
    }

    template<typename... Args>
    void Info(const char* fmt, const Args&... args) {
        logger_->info(fmt, args...);
    }

    template<typename... Args>
    void Warn(const char* fmt, const Args&... args) {
        logger_->warn(fmt, args...);
    }

    template<typename... Args>
    void Error(const char* fmt, const Args&... args) {
        logger_->error(fmt, args...);
    }

    template<typename... Args>
    void Critical(const char* fmt, const Args&... args) {
        logger_->critical(fmt, args...);
    }

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::shared_ptr<spdlog::logger> logger_;
};

} // namespace logging
} // namespace utoolkit

// 便捷宏定义 - 原始格式
#define UTOOLKIT_LOG_TRACE(...) utoolkit::logging::Logger::GetInstance().Trace(__VA_ARGS__)
#define UTOOLKIT_LOG_DEBUG(...) utoolkit::logging::Logger::GetInstance().Debug(__VA_ARGS__)
#define UTOOLKIT_LOG_INFO(...) utoolkit::logging::Logger::GetInstance().Info(__VA_ARGS__)
#define UTOOLKIT_LOG_WARN(...) utoolkit::logging::Logger::GetInstance().Warn(__VA_ARGS__)
#define UTOOLKIT_LOG_ERROR(...) utoolkit::logging::Logger::GetInstance().Error(__VA_ARGS__)
#define UTOOLKIT_LOG_CRITICAL(...) utoolkit::logging::Logger::GetInstance().Critical(__VA_ARGS__)

// FMT格式宏定义 - 兼容pipeline/logger.h中的使用方式
#define UT_TRACE_FMT(...) utoolkit::logging::Logger::GetInstance().Trace(__VA_ARGS__)
#define UT_DEBUG_FMT(...) utoolkit::logging::Logger::GetInstance().Debug(__VA_ARGS__)
#define UT_INFO_FMT(...) utoolkit::logging::Logger::GetInstance().Info(__VA_ARGS__)
#define UT_WARN_FMT(...) utoolkit::logging::Logger::GetInstance().Warn(__VA_ARGS__)
#define UT_ERROR_FMT(...) utoolkit::logging::Logger::GetInstance().Error(__VA_ARGS__)
#define UT_FATAL_FMT(...) utoolkit::logging::Logger::GetInstance().Critical(__VA_ARGS__)

// 基本日志宏
#define UT_TRACE(...) UT_TRACE_FMT(__VA_ARGS__)
#define UT_DEBUG(...) UT_DEBUG_FMT(__VA_ARGS__)
#define UT_INFO(...) UT_INFO_FMT(__VA_ARGS__)
#define UT_WARN(...) UT_WARN_FMT(__VA_ARGS__)
#define UT_ERROR(...) UT_ERROR_FMT(__VA_ARGS__)
#define UT_FATAL(...) UT_FATAL_FMT(__VA_ARGS__)

#endif // UTOOLKIT_LOGGING_LOGGER_H