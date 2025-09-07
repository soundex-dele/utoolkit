#include <utoolkit/utils/string_utils.h>
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <sstream>

namespace utoolkit {
namespace utils {

std::string StringUtils::trim(const std::string& str) {
    return trim_left(trim_right(str));
}

std::string StringUtils::trim_left(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : str.substr(start);
}

std::string StringUtils::trim_right(const std::string& str) {
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string StringUtils::to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string StringUtils::to_upper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool StringUtils::starts_with(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && 
           str.compare(0, prefix.size(), prefix) == 0;
}

bool StringUtils::ends_with(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && 
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::vector<std::string> StringUtils::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    
    return result;
}

std::vector<std::string> StringUtils::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    
    result.push_back(str.substr(start));
    return result;
}

std::string StringUtils::join(const std::vector<std::string>& parts, const std::string& delimiter) {
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i != 0) {
            result += delimiter;
        }
        result += parts[i];
    }
    return result;
}

std::string StringUtils::replace(const std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos) {
        return str;
    }
    
    std::string result = str;
    result.replace(start_pos, from.length(), to);
    return result;
}

std::string StringUtils::replace_all(const std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) {
        return str;
    }
    
    std::string result = str;
    size_t start_pos = 0;
    
    while ((start_pos = result.find(from, start_pos)) != std::string::npos) {
        result.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    
    return result;
}

bool StringUtils::contains(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

std::string StringUtils::substring(const std::string& str, size_t pos, size_t len) {
    if (pos >= str.length()) {
        return "";
    }
    return str.substr(pos, len);
}

int StringUtils::to_int(const std::string& str) {
    return std::stoi(str);
}

double StringUtils::to_double(const std::string& str) {
    return std::stod(str);
}

long StringUtils::to_long(const std::string& str) {
    return std::stol(str);
}

bool StringUtils::to_bool(const std::string& str) {
    std::string lower = to_lower(trim(str));
    return lower == "true" || lower == "1" || lower == "yes" || lower == "on";
}

std::string StringUtils::from_int(int value) {
    return std::to_string(value);
}

std::string StringUtils::from_double(double value, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    
    std::string result = ss.str();
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    if (result.back() == '.') {
        result.pop_back();
    }
    
    return result;
}

std::string StringUtils::from_long(long value) {
    return std::to_string(value);
}

std::string StringUtils::from_bool(bool value) {
    return value ? "true" : "false";
}

bool StringUtils::is_integer(const std::string& str) {
    try {
        size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}

bool StringUtils::is_float(const std::string& str) {
    try {
        size_t pos;
        std::stod(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}

bool StringUtils::is_numeric(const std::string& str) {
    return is_integer(str) || is_float(str);
}

std::string StringUtils::format(const std::string& format_str, ...) {
    va_list args;
    va_start(args, format_str);
    
    va_list args_copy;
    va_copy(args_copy, args);
    
    int size = vsnprintf(nullptr, 0, format_str.c_str(), args_copy);
    va_end(args_copy);
    
    if (size < 0) {
        va_end(args);
        return "";
    }
    
    std::vector<char> buffer(size + 1);
    vsnprintf(buffer.data(), buffer.size(), format_str.c_str(), args);
    va_end(args);
    
    return std::string(buffer.data());
}

std::string StringUtils::repeat(const std::string& str, size_t count) {
    std::string result;
    result.reserve(str.length() * count);
    for (size_t i = 0; i < count; ++i) {
        result += str;
    }
    return result;
}

std::string StringUtils::pad_left(const std::string& str, size_t width, char pad_char) {
    if (str.length() >= width) {
        return str;
    }
    return repeat(std::string(1, pad_char), width - str.length()) + str;
}

std::string StringUtils::pad_right(const std::string& str, size_t width, char pad_char) {
    if (str.length() >= width) {
        return str;
    }
    return str + repeat(std::string(1, pad_char), width - str.length());
}

} // namespace utils
} // namespace utoolkit