#pragma once

#include <chrono>
#include <string>

namespace utoolkit {
namespace utils {

class TimeUtils {
public:
    static std::string get_current_timestamp();
    static std::string get_current_date();
    static std::string get_current_time();
    static int64_t get_timestamp_ms();
    static int64_t get_timestamp_us();
    static std::string format_duration(std::chrono::milliseconds duration);
    static std::string format_duration_us(std::chrono::microseconds duration);
    static void sleep_ms(int milliseconds);
    static void sleep_us(int microseconds);
    
    class Timer {
    public:
        Timer();
        void start();
        void stop();
        void reset();
        std::chrono::milliseconds elapsed_ms() const;
        std::chrono::microseconds elapsed_us() const;
        std::string elapsed_str() const;
    
    private:
        std::chrono::steady_clock::time_point start_time_;
        std::chrono::steady_clock::time_point end_time_;
        bool running_;
    };
};

} // namespace utils
} // namespace utoolkit