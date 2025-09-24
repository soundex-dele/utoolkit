#include <utoolkit/utils/file_utils.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <io.h>
#define mkdir(path, mode) _mkdir(path)
#define access _access
#define F_OK 0
#else
#include <unistd.h>
#endif

namespace utoolkit {
namespace utils {

bool FileUtils::exists(const std::string& path) {
    return access(path.c_str(), F_OK) == 0;
}

bool FileUtils::is_file(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        return false;
    }
    return S_ISREG(st.st_mode);
}

bool FileUtils::is_directory(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        return false;
    }
    return S_ISDIR(st.st_mode);
}

bool FileUtils::create_directory(const std::string& path) {
#ifdef _WIN32
    return _mkdir(path.c_str()) == 0;
#else
    return mkdir(path.c_str(), 0755) == 0;
#endif
}

bool FileUtils::create_directories(const std::string& path) {
    if (exists(path)) {
        return true;
    }
    
    size_t pos = 0;
    do {
        pos = path.find('/', pos + 1);
        std::string sub_path = path.substr(0, pos);
        if (!sub_path.empty() && !exists(sub_path)) {
            if (!create_directory(sub_path)) {
                return false;
            }
        }
    } while (pos != std::string::npos);
    
    return true;
}

bool FileUtils::remove_file(const std::string& path) {
    return std::remove(path.c_str()) == 0;
}

bool FileUtils::remove_directory(const std::string& path) {
#ifdef _WIN32
    return RemoveDirectoryA(path.c_str()) != 0;
#else
    return rmdir(path.c_str()) == 0;
#endif
}

std::string FileUtils::get_filename(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(pos + 1);
}

std::string FileUtils::get_directory(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return ".";
    }
    return path.substr(0, pos);
}

std::string FileUtils::get_extension(const std::string& path) {
    size_t pos = path.find_last_of('.');
    if (pos == std::string::npos || pos == path.length() - 1) {
        return "";
    }
    return path.substr(pos + 1);
}

std::string FileUtils::get_basename(const std::string& path) {
    std::string filename = get_filename(path);
    size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos) {
        return filename;
    }
    return filename.substr(0, pos);
}

std::string FileUtils::join_path(const std::string& path1, const std::string& path2) {
    if (path1.empty()) return path2;
    if (path2.empty()) return path1;
    
    char last_char = path1.back();
    if (last_char == '/' || last_char == '\\') {
        return path1 + path2;
    } else {
        return path1 + "/" + path2;
    }
}

std::string FileUtils::get_current_working_directory() {
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::string(buffer);
    }
    return "";
}

std::string FileUtils::get_executable_directory() {
    char buffer[PATH_MAX];
    ssize_t len = 0;
#ifdef _WIN32
    len = GetModuleFileNameA(nullptr, buffer, PATH_MAX);
#else
    len = readlink("/proc/self/exe", buffer, PATH_MAX);
    if (len == -1) {
        len = readlink("/proc/curproc/file", buffer, PATH_MAX);
    }
    if (len == -1) {
        len = readlink("/proc/self/path/a.out", buffer, PATH_MAX);
    }
#endif
    if (len > 0) {
        buffer[len] = '\0';
        return get_directory(std::string(buffer));
    }
    return get_current_working_directory();
}

std::vector<std::string> FileUtils::list_files(const std::string& directory) {
    std::vector<std::string> files;
    DIR* dir = opendir(directory.c_str());
    if (dir != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                files.push_back(entry->d_name);
            }
        }
        closedir(dir);
    }
    return files;
}

std::vector<std::string> FileUtils::list_directories(const std::string& directory) {
    std::vector<std::string> dirs;
    DIR* dir = opendir(directory.c_str());
    if (dir != nullptr) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_DIR && 
                strcmp(entry->d_name, ".") != 0 && 
                strcmp(entry->d_name, "..") != 0) {
                dirs.push_back(entry->d_name);
            }
        }
        closedir(dir);
    }
    return dirs;
}

bool FileUtils::read_file(const std::string& filename, std::string& content) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    content.assign(std::istreambuf_iterator<char>(file), 
                   std::istreambuf_iterator<char>());
    return true;
}

bool FileUtils::write_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file.write(content.c_str(), content.size());
    return file.good();
}

bool FileUtils::append_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        return false;
    }
    
    file.write(content.c_str(), content.size());
    return file.good();
}

uint64_t FileUtils::get_file_size(const std::string& filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) {
        return 0;
    }
    return static_cast<uint64_t>(st.st_size);
}

bool FileUtils::is_readable(const std::string& filename) {
    return access(filename.c_str(), R_OK) == 0;
}

bool FileUtils::is_writable(const std::string& filename) {
    return access(filename.c_str(), W_OK) == 0;
}

std::string FileUtils::get_temp_directory() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetTempPathA(MAX_PATH, buffer);
    return std::string(buffer);
#else
    const char* tmpdir = getenv("TMPDIR");
    if (tmpdir == nullptr) tmpdir = "/tmp";
    return std::string(tmpdir);
#endif
}

std::string FileUtils::create_temp_file(const std::string& prefix) {
    std::string temp_dir = get_temp_directory();
    std::string temp_file = join_path(temp_dir, prefix + "XXXXXX");
    
#ifdef _WIN32
    char temp_path[MAX_PATH];
    if (GetTempFileNameA(temp_dir.c_str(), prefix.c_str(), 0, temp_path) != 0) {
        return std::string(temp_path);
    }
    return "";
#else
    char* temp_path = strdup(temp_file.c_str());
    int fd = mkstemp(temp_path);
    if (fd != -1) {
        close(fd);
        std::string result(temp_path);
        free(temp_path);
        return result;
    }
    free(temp_path);
    return "";
#endif
}

} // namespace utils
} // namespace utoolkit