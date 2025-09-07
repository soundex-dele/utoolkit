# task_queue测试

# 查找测试源文件
file(GLOB TEST_SOURCES "test_*.cpp")

# 创建测试可执行文件
add_executable(task_queue_tests ${TEST_SOURCES})

# 链接task_queue库
target_link_libraries(task_queue_tests PRIVATE utoolkit_task_queue)

# 条件链接GoogleTest
if(TARGET gtest)
    target_link_libraries(task_queue_tests PRIVATE gtest gtest_main)
    add_test(NAME task_queue_tests COMMAND task_queue_tests)
endif()

# 设置C++标准
target_compile_features(task_queue_tests PRIVATE cxx_std_17)

# 设置包含目录
target_include_directories(task_queue_tests PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)