cmake_minimum_required(VERSION 3.10)
project(utoolkit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 版本信息
set(UTOOLKIT_VERSION_MAJOR 1)
set(UTOOLKIT_VERSION_MINOR 0)
set(UTOOLKIT_VERSION_PATCH 0)

# 选项
option(UTOOLKIT_BUILD_EXAMPLES "Build examples" OFF)
option(UTOOLKIT_BUILD_TESTS "Build tests" OFF)
option(UTOOLKIT_INSTALL "Enable installation" ON)

# 第三方依赖
add_subdirectory(third_party)

# 添加子模块
add_subdirectory(logging)
add_subdirectory(threadpool)
add_subdirectory(utils)
add_subdirectory(task_queue)

# 主库 - 头文件集合
add_library(utoolkit INTERFACE)
target_link_libraries(utoolkit INTERFACE
    utoolkit_logging
    utoolkit_threadpool
    utoolkit_utils
    utoolkit_task_queue
        spdlog_interface
)

# 包含目录
target_include_directories(utoolkit INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 安装主库
if(UTOOLKIT_INSTALL)
    install(TARGETS utoolkit
        EXPORT utoolkit-targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
    )
    
#    install(EXPORT utoolkit-targets
#        FILE utoolkit-targets.cmake
#        NAMESPACE utoolkit::
#        DESTINATION lib/cmake/utoolkit
#    )
#
#    include(CMakePackageConfigHelpers)
#    configure_package_config_file(
#        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/utoolkit-config.cmake.in
#        ${CMAKE_CURRENT_BINARY_DIR}/utoolkit-config.cmake
#        INSTALL_DESTINATION lib/cmake/utoolkit
#    )
#
#    install(FILES
#        ${CMAKE_CURRENT_BINARY_DIR}/utoolkit-config.cmake
#        DESTINATION lib/cmake/utoolkit
#    )
endif()

# 全局示例
if(UTOOLKIT_BUILD_EXAMPLES)
    add_subdirectory(third_party/examples)
endif()

# 测试由各个模块自行管理
if(UTOOLKIT_BUILD_TESTS)
    enable_testing()
    set(LOGGING_BUILD_TESTS ON)
    set(THREADPOOL_BUILD_TESTS ON)
    set(TASK_QUEUE_BUILD_TESTS ON)
    set(UTILS_BUILD_TESTS ON)
endif()