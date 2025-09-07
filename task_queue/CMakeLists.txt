# task_queue模块

# 设置源文件
set(TASK_QUEUE_SOURCES
    src/event.cpp
    src/task_queue.cpp
    src/task_queue_base.cpp
    src/task_queue_manager.cpp
    src/task_queue_std.cpp
)

# 设置头文件
set(TASK_QUEUE_HEADERS
    include/utoolkit/task_queue/event.h
    include/utoolkit/task_queue/queued_task.h
    include/utoolkit/task_queue/task_queue.h
    include/utoolkit/task_queue/task_queue_base.h
    include/utoolkit/task_queue/task_queue_manager.h
    include/utoolkit/task_queue/task_queue_std.h
)

# 创建静态库
add_library(utoolkit_task_queue STATIC ${TASK_QUEUE_SOURCES} ${TASK_QUEUE_HEADERS})

# 设置包含目录
target_include_directories(utoolkit_task_queue
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 设置C++标准
target_compile_features(utoolkit_task_queue PRIVATE cxx_std_17)

# 安装规则
install(TARGETS utoolkit_task_queue
    EXPORT utoolkit_task_queue_targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# 添加示例
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples)
    add_subdirectory(examples)
endif()

# 添加测试（如果启用）
if(UTOOLKIT_BUILD_TESTS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_subdirectory(tests)
endif()