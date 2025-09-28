#pragma once

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

// 便捷宏定义
#define UTOOLKIT_LOG_TRACE(...) utoolkit::logging::Logger::GetInstance().Trace(__VA_ARGS__)
#define UTOOLKIT_LOG_DEBUG(...) utoolkit::logging::Logger::GetInstance().Debug(__VA_ARGS__)
#define UTOOLKIT_LOG_INFO(...) utoolkit::logging::Logger::GetInstance().Info(__VA_ARGS__)
#define UTOOLKIT_LOG_WARN(...) utoolkit::logging::Logger::GetInstance().Warn(__VA_ARGS__)
#define UTOOLKIT_LOG_ERROR(...) utoolkit::logging::Logger::GetInstance().Error(__VA_ARGS__)
#define UTOOLKIT_LOG_CRITICAL(...) utoolkit::logging::Logger::GetInstance().Critical(__VA_ARGS__)