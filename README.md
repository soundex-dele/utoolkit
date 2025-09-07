# utoolkit - 跨平台C++基础组件库

utoolkit是一个现代化的C++跨平台基础组件库，提供了日志系统、线程池、时间工具、文件系统工具和字符串工具等常用功能。该库设计简洁、易于使用，支持Windows、Linux和macOS平台。

## 特性

- **跨平台支持**: 支持Windows、Linux、macOS
- **现代C++**: 基于C++17标准
- **线程安全**: 所有组件都考虑线程安全
- **易于集成**: 仅需包含头文件即可使用
- **丰富功能**: 涵盖日志、线程池、文件操作、时间处理等
- **单元测试**: 完整的Google Test测试套件

## 组件概览

### 1. 日志系统 (Logger)
- 多级别日志记录 (TRACE, DEBUG, INFO, WARN, ERROR, FATAL)
- 文件和控制台输出
- 时间戳和文件位置信息
- 线程安全

### 2. 线程池 (ThreadPool)
- 任务队列管理
- 动态线程数量配置
- 支持任意参数和返回类型的任务
- 优雅的关闭机制

### 3. 时间工具 (TimeUtils)
- 高精度时间戳
- 计时器功能
- 时间格式化和解析
- 跨平台时间操作

### 4. 文件系统工具 (FileUtils)
- 文件和目录操作
- 路径处理
- 文件读写
- 临时文件创建

### 5. 字符串工具 (StringUtils)
- 字符串格式化和转换
- 类型转换
- 文本处理
- 正则表达式支持

## 快速开始

### 构建项目

#### Linux/macOS
```bash
chmod +x build.sh
./build.sh
```

#### Windows
```batch
build.bat
```

### 使用示例

#### 基础使用
```cpp
#include "utoolkit/utoolkit.h"

int main() {
    // 日志系统
    UT_INFO("Hello, utoolkit!");
    
    // 线程池
    ThreadPool pool(4);
    auto future = pool.enqueue([]() { return 42; });
    std::cout << "Result: " << future.get() << std::endl;
    
    // 时间工具
    auto timestamp = TimeUtils::get_current_timestamp();
    std::cout << "Current time: " << timestamp << std::endl;
    
    // 文件工具
    FileUtils::write_file("test.txt", "Hello World");
    
    // 字符串工具
    std::string upper = StringUtils::to_upper("hello");
    std::cout << "Uppercase: " << upper << std::endl;
    
    return 0;
}
```

## 详细文档

### 日志系统

```cpp
#include "utoolkit/logging/logger.h"

// 设置日志级别
Logger::instance().set_log_level(LogLevel::DEBUG);

// 设置日志文件
Logger::instance().set_log_file("app.log");

// 使用宏记录日志
UT_INFO("Application started");
UT_ERROR("Something went wrong: %s", error_message);
```

### 线程池

```cpp
#include "utoolkit/threadpool/threadpool.h"

// 创建线程池
ThreadPool pool(4); // 4个工作线程

// 提交任务
auto future = pool.enqueue([](int x, int y) {
    return x + y;
}, 10, 20);

int result = future.get(); // 30
```

### 时间工具

```cpp
#include "utoolkit/utils/time_utils.h"

// 获取当前时间戳
auto timestamp = TimeUtils::get_current_timestamp();

// 计时器
TimeUtils::Timer timer;
timer.start();
// ... 执行操作 ...
timer.stop();
std::cout << "Elapsed: " << timer.elapsed_str() << std::endl;
```

### 文件系统工具

```cpp
#include "utoolkit/utils/file_utils.h"

// 文件操作
FileUtils::write_file("data.txt", "content");
std::string content;
FileUtils::read_file("data.txt", content);

// 目录操作
FileUtils::create_directories("path/to/directory");
auto files = FileUtils::list_files("directory");
```

### 字符串工具

```cpp
#include "utoolkit/utils/string_utils.h"

// 字符串处理
std::string trimmed = StringUtils::trim("  hello  ");
std::vector<std::string> parts = StringUtils::split("a,b,c", ',');
std::string joined = StringUtils::join(parts, "-");

// 类型转换
int value = StringUtils::to_int("42");
std::string str = StringUtils::from_int(42);
```

## 构建选项

### CMake配置

```bash
# 基本构建
cmake -B build
cmake --build build

# 禁用测试
cmake -B build -DUT_BUILD_TESTS=OFF

# 禁用示例
cmake -B build -DUT_BUILD_EXAMPLES=OFF

# 调试构建
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

## 依赖

- **编译器**: C++17兼容编译器 (GCC 7+, Clang 5+, MSVC 2019+)
- **构建系统**: CMake 3.15+
- **线程库**: 标准C++线程库
- **测试框架**: Google Test (自动获取)

## 平台支持

| 平台 | 编译器 | 状态 |
|------|--------|------|
| Linux | GCC 7+ | ✅ |
| Linux | Clang 5+ | ✅ |
| macOS | Clang | ✅ |
| Windows | MSVC 2019+ | ✅ |
| Windows | MinGW | ✅ |

## 贡献

欢迎提交Issue和Pull Request！

## 许可证

MIT License - 详见LICENSE文件