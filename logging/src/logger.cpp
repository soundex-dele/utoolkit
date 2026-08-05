#include "utoolkit/logging/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

namespace utoolkit {
namespace logging {

// Impl类的完整实现
class Logger::Impl {
public:
    Impl() : logger_(nullptr) {
    }

    ~Impl() {
        // spdlog会自动管理logger的生命周期
    }

    void Initialize(const std::string& logger_name, 
                   const std::string& pattern, 
                   LogLevel level) {
        std::lock_guard<std::mutex> lock(mutex_);
        try {
            // 创建控制台颜色接收器
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern(pattern);

            // 创建文件接收器（带日志轮转功能，最大10MB，保留3个文件）
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                "logs/" + logger_name + ".log", 1024 * 1024 * 10, 3);
            file_sink->set_pattern(pattern);

            // 创建多接收器日志器
            std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
            logger_ = std::make_shared<spdlog::logger>(
                logger_name, sinks.begin(), sinks.end());
            
            // 设置日志级别
            logger_->set_level(ToSpdlogLevel(level));
            
            // 设置为默认日志器
            spdlog::set_default_logger(logger_);
            
            logger_->info("Logger initialized successfully");
        } catch (const spdlog::spdlog_ex& ex) {
            std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
            throw;
        }
    }

    void SetLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            logger_->set_level(ToSpdlogLevel(level));
        }
    }

    LogLevel GetLevel() const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            return FromSpdlogLevel(logger_->level());
        }
        return LogLevel::Info;
    }

    template<typename... Args>
    void Trace(const char* fmt, const Args&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            logger_->trace(fmt, args...);
        }
    }

    template<typename... Args>
    void Debug(const char* fmt, const Args&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            logger_->debug(fmt, args...);
        }
    }

    template<typename... Args>
    void Info(const char* fmt, const Args&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            logger_->info(fmt, args...);
        }
    }

    template<typename... Args>
    void Warn(const char* fmt, const Args&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            logger_->warn(fmt, args...);
        }
    }

    template<typename... Args>
    void Error(const char* fmt, const Args&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            logger_->error(fmt, args...);
        }
    }

    template<typename... Args>
    void Critical(const char* fmt, const Args&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logger_) {
            logger_->critical(fmt, args...);
        }
    }

private:
    mutable std::mutex mutex_;
    std::shared_ptr<spdlog::logger> logger_;

    // 转换内部LogLevel到spdlog的level_enum
    spdlog::level::level_enum ToSpdlogLevel(LogLevel level) const {
        switch (level) {
            case LogLevel::Trace:
                return spdlog::level::trace;
            case LogLevel::Debug:
                return spdlog::level::debug;
            case LogLevel::Info:
                return spdlog::level::info;
            case LogLevel::Warn:
                return spdlog::level::warn;
            case LogLevel::Error:
                return spdlog::level::err;
            case LogLevel::Critical:
                return spdlog::level::critical;
            default:
                return spdlog::level::info;
        }
    }

    // 转换spdlog的level_enum到内部LogLevel
    LogLevel FromSpdlogLevel(spdlog::level::level_enum level) const {
        switch (level) {
            case spdlog::level::trace:
                return LogLevel::Trace;
            case spdlog::level::debug:
                return LogLevel::Debug;
            case spdlog::level::info:
                return LogLevel::Info;
            case spdlog::level::warn:
                return LogLevel::Warn;
            case spdlog::level::err:
                return LogLevel::Error;
            case spdlog::level::critical:
                return LogLevel::Critical;
            default:
                return LogLevel::Info;
        }
    }
};

Logger::Logger() : impl_(std::make_shared<Impl>()) {}

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

// Logger类方法的实现
void Logger::Initialize(const std::string& logger_name, 
                       const std::string& pattern, 
                       LogLevel level) {
    impl_->Initialize(logger_name, pattern, level);
}

void Logger::SetLevel(LogLevel level) {
    if (impl_) {
        impl_->SetLevel(level);
    }
}

LogLevel Logger::GetLevel() const {
    if (impl_) {
        return impl_->GetLevel();
    }
    return LogLevel::Info;
}

void Logger::Trace(const char* msg) {
    if (impl_) {
        impl_->Trace(msg);
    }
}

void Logger::Debug(const char* msg) {
    if (impl_) {
        impl_->Debug(msg);
    }
}

void Logger::Info(const char* msg) {
    if (impl_) {
        impl_->Info(msg);
    }
}

void Logger::Warn(const char* msg) {
    if (impl_) {
        impl_->Warn(msg);  
    }
}

void Logger::Error(const char* msg) {
    if (impl_) {
        impl_->Error(msg);
    }
}

void Logger::Critical(const char* msg) {
    if (impl_) {
        impl_->Critical(msg);
    }
}

} // namespace logging
} // namespace utoolkit
