#include <utoolkit/logging/logger.h>
#include <iostream>
#include <string>

using namespace utoolkit::logging;

int main() {
    std::cout << "=== Advanced Logger Example ===" << std::endl;
    
    // 获取日志实例并设置日志级别
    Logger& logger = Logger::instance();
    logger.set_log_level(LogLevel::TRACE);
    
    std::cout << "\n1. 基本日志宏测试:" << std::endl;
    UT_TRACE("这是一条TRACE级别日志");
    UT_DEBUG("这是一条DEBUG级别日志");
    UT_INFO("这是一条INFO级别日志");
    UT_WARN("这是一条WARN级别日志");
    UT_ERROR("这是一条ERROR级别日志");
    UT_FATAL("这是一条FATAL级别日志");
    
    std::cout << "\n2. 格式化日志宏测试:" << std::endl;
    int number = 42;
    double pi = 3.14159;
    std::string name = "utoolkit";
    
    UT_TRACE_FMT("整数: %d, 浮点数: %.2f", number, pi);
    UT_DEBUG_FMT("名称: %s, 版本: %d.%d.%d", name.c_str(), 1, 0, 0);
    UT_INFO_FMT("用户ID: %d, 状态码: %d", 12345, 200);
    UT_WARN_FMT("磁盘空间不足: %.2f%% 剩余", 10.5);
    UT_ERROR_FMT("连接失败: 错误码=%d, 消息=%s", -1, "无法连接到服务器");
    UT_FATAL_FMT("系统崩溃: 原因=%s, 位置=%s", "内存不足", "模块A");
    
    std::cout << "\n3. 条件日志宏测试:" << std::endl;
    bool condition_true = true;
    bool condition_false = false;
    
    UT_DEBUG_IF(condition_true, "这个条件为真，日志会显示");
    UT_DEBUG_IF(condition_false, "这个条件为假，日志不会显示");
    
    std::cout << "\n4. 条件格式化日志宏测试:" << std::endl;
    int value = 100;
    
    UT_INFO_IF_FMT(value > 50, "值 %d 大于 50", value);
    UT_WARN_IF_FMT(value < 0, "值 %d 小于 0", value); // 不会显示
    
    // 演示文件日志
    std::cout << "\n5. 文件日志测试:" << std::endl;
    logger.set_log_file("advanced_log.txt");
    UT_INFO("这条日志会写入文件");
    UT_INFO_FMT("格式化日志也会写入文件: %s", "测试成功");
    
    // 测试控制台输出开关
    std::cout << "\n6. 控制台输出开关测试:" << std::endl;
    std::cout << "关闭控制台输出后，只有文件日志会记录" << std::endl;
    logger.enable_console_output(false);
    UT_INFO("这条日志只会写入文件，不会显示在控制台");
    
    // 重新开启控制台输出
    logger.enable_console_output(true);
    UT_INFO("控制台输出已重新开启");
    
    std::cout << "\n日志测试完成，请查看advanced_log.txt文件" << std::endl;
    return 0;
}