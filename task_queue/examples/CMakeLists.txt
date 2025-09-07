# task_queue示例

# 创建示例可执行文件
add_executable(example_task_queue example_task_queue.cpp)

# 链接task_queue库
target_link_libraries(example_task_queue PRIVATE utoolkit_task_queue)

# 设置C++标准
target_compile_features(example_task_queue PRIVATE cxx_std_17)

# 设置包含目录
target_include_directories(example_task_queue PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)