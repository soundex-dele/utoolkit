#include <string>
#include <vector>
#include <iostream>

// 如果fmt可用，包含头文件
#ifdef HAVE_FMT
#include <fmt/core.h>
#include <fmt/format.h>
#endif

int main() {
#ifdef HAVE_FMT
    // 基本格式化
    std::string message = fmt::format("Hello, {}!", "World");
    std::cout << message << std::endl;
    
    // 精度控制
    double pi = 3.14159265359;
    std::cout << fmt::format("Pi = {:.2f}", pi) << std::endl;
    
    // 容器格式化
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << fmt::format("Numbers: {}", fmt::join(numbers, ", ")) << std::endl;
    
    // 命名参数
    std::cout << fmt::format("Name: {name}, Age: {age}", 
                           fmt::arg("name", "Alice"), 
                           fmt::arg("age", 30)) << std::endl;
#else
    std::cout << "fmt library not available" << std::endl;
#endif
    return 0;
}