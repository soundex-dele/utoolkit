#include <utoolkit/utils/time_utils.h>
#include <iomanip>
#include <sstream>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace utoolkit {
namespace utils {

std::string TimeUtils::get_current_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();
    
    return ss.str();
}

std::string TimeUtils::get_current_date() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d");
    
    return ss.str();
}

std::string TimeUtils::get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
    
    return ss.str();
}

int64_t TimeUtils::get_timestamp_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

int64_t TimeUtils::get_timestamp_us() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string TimeUtils::format_duration(std::chrono::milliseconds duration) {
    auto total_ms = duration.count();
    
    int hours = static_cast<int>(total_ms / 3600000);
    int minutes = static_cast<int>((total_ms % 3600000) / 60000);
    int seconds = static_cast<int>((total_ms % 60000) / 1000);
    int milliseconds = static_cast<int>(total_ms % 1000);
    
    std::stringstream ss;
    if (hours > 0) {
        ss << hours << "h ";
    }
    if (minutes > 0 || hours > 0) {
        ss << minutes << "m ";
    }
    if (seconds > 0 || minutes > 0 || hours > 0) {
        ss << seconds << "s ";
    }
    ss << milliseconds << "ms";
    
    return ss.str();
}

std::string TimeUtils::format_duration_us(std::chrono::microseconds duration) {
    auto total_us = duration.count();
    
    int hours = static_cast<int>(total_us / 3600000000LL);
    int minutes = static_cast<int>((total_us % 3600000000LL) / 60000000);
    int seconds = static_cast<int>((total_us % 60000000) / 1000000);
    int milliseconds = static_cast<int>((total_us % 1000000) / 1000);
    int microseconds = static_cast<int>(total_us % 1000);
    
    std::stringstream ss;
    if (hours > 0) {
        ss << hours << "h ";
    }
    if (minutes > 0 || hours > 0) {
        ss << minutes << "m ";
    }
    if (seconds > 0 || minutes > 0 || hours > 0) {
        ss << seconds << "s ";
    }
    if (milliseconds > 0 || seconds > 0 || minutes > 0 || hours > 0) {
        ss << milliseconds << "ms ";
    }
    ss << microseconds << "μs";
    
    return ss.str();
}

void TimeUtils::sleep_ms(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void TimeUtils::sleep_us(int microseconds) {
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}

TimeUtils::Timer::Timer() : running_(false) {}

void TimeUtils::Timer::start() {
    start_time_ = std::chrono::steady_clock::now();
    running_ = true;
}

void TimeUtils::Timer::stop() {
    if (running_) {
        end_time_ = std::chrono::steady_clock::now();
        running_ = false;
    }
}

void TimeUtils::Timer::reset() {
    running_ = false;
}

std::chrono::milliseconds TimeUtils::Timer::elapsed_ms() const {
    if (running_) {
        auto end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_time_);
    } else {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - start_time_);
    }
}

std::chrono::microseconds TimeUtils::Timer::elapsed_us() const {
    if (running_) {
        auto end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start_time_);
    } else {
        return std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - start_time_);
    }
}

std::string TimeUtils::Timer::elapsed_str() const {
    return format_duration(elapsed_ms());
}

} // namespace utils
} // namespace utoolkit