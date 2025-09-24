#pragma once

#include <string>
#include <vector>
#include <iomanip>

namespace utoolkit {
namespace utils {

class StringUtils {
public:
    static std::string trim(const std::string& str);
    static std::string trim_left(const std::string& str);
    static std::string trim_right(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    static std::string join(const std::vector<std::string>& parts, const std::string& delimiter);
    static bool starts_with(const std::string& str, const std::string& prefix);
    static bool ends_with(const std::string& str, const std::string& suffix);
    static std::string to_lower(const std::string& str);
    static std::string to_upper(const std::string& str);
    static bool contains(const std::string& str, const std::string& substring);
    static std::string replace(const std::string& str, const std::string& from, const std::string& to);
    static std::string replace_all(const std::string& str, const std::string& from, const std::string& to);
    
    static std::string substring(const std::string& str, size_t pos, size_t len = std::string::npos);
    static int to_int(const std::string& str);
    static double to_double(const std::string& str);
    static long to_long(const std::string& str);
    static bool to_bool(const std::string& str);
    static std::string from_int(int value);
    static std::string from_double(double value, int precision = 2);
    static std::string from_long(long value);
    static std::string from_bool(bool value);
    static bool is_integer(const std::string& str);
    static bool is_float(const std::string& str);
    static bool is_numeric(const std::string& str);
    static std::string format(const std::string& format_str, ...);
    static std::string repeat(const std::string& str, size_t count);
    static std::string pad_left(const std::string& str, size_t width, char pad_char = ' ');
    static std::string pad_right(const std::string& str, size_t width, char pad_char = ' ');
};

} // namespace utils
} // namespace utoolkit