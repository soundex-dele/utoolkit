#include "utoolkit/logging/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/common.h"

#include <iostream>
#include <vector>

namespace utoolkit {
namespace logging {

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

void Logger::Initialize(const std::string& logger_name,
                       const std::string& pattern,
                       spdlog::level::level_enum level) {
    try {
        // Create console color sink
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern(pattern);

        // Create file sink with rotation (max 10MB, keep 3 files)
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/utoolkit.log", 1024 * 1024 * 10, 3);
        file_sink->set_pattern(pattern);

        // Create multi-sink logger
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
        logger_ = std::make_shared<spdlog::logger>(logger_name, sinks.begin(), sinks.end());
        
        // Set log level
        logger_->set_level(level);
        
        // Set as default logger
        set_default_logger(logger_);
        
        logger_->info("Logger initialized successfully");
    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
        throw;
    }
}

void Logger::SetLevel(spdlog::level::level_enum level) {
    if (logger_) {
        logger_->set_level(level);
    }
}

spdlog::level::level_enum Logger::GetLevel() const {
    return logger_ ? logger_->level() : spdlog::level::off;
}

} // namespace logging
} // namespace utoolkit