#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace utoolkit {
namespace utils {

class FileUtils {
public:
    static bool exists(const std::string& path);
    static bool is_file(const std::string& path);
    static bool is_directory(const std::string& path);
    static bool create_directory(const std::string& path);
    static bool create_directories(const std::string& path);
    static bool remove_file(const std::string& path);
    static bool remove_directory(const std::string& path);
    static std::string get_filename(const std::string& path);
    static std::string get_directory(const std::string& path);
    static std::string get_extension(const std::string& path);
    static std::string get_basename(const std::string& path);
    static std::string join_path(const std::string& path1, const std::string& path2);
    static std::string get_current_working_directory();
    static std::string get_executable_directory();
    static std::vector<std::string> list_files(const std::string& directory);
    static std::vector<std::string> list_directories(const std::string& directory);
    static bool read_file(const std::string& filename, std::string& content);
    static bool write_file(const std::string& filename, const std::string& content);
    static bool append_file(const std::string& filename, const std::string& content);
    static uint64_t get_file_size(const std::string& filename);
    static bool is_readable(const std::string& filename);
    static bool is_writable(const std::string& filename);
    static std::string get_temp_directory();
    static std::string create_temp_file(const std::string& prefix = "tmp");
};

} // namespace utils
} // namespace utoolkit