cmake_minimum_required(VERSION 3.10)
project(utoolkit_threadpool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADPOOL_SOURCES
    src/threadpool.cpp
)

add_library(utoolkit_threadpool STATIC ${THREADPOOL_SOURCES})

target_include_directories(utoolkit_threadpool
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(Threads REQUIRED)
target_link_libraries(utoolkit_threadpool Threads::Threads)

# 安装规则
install(TARGETS utoolkit_threadpool
    EXPORT utoolkit-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/utoolkit/threadpool
    FILES_MATCHING PATTERN "*.h"
)

# 示例
option(THREADPOOL_BUILD_EXAMPLES "Build threadpool examples" OFF)
if(THREADPOOL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# 测试
option(THREADPOOL_BUILD_TESTS "Build threadpool tests" OFF)
if(THREADPOOL_BUILD_TESTS)
    add_subdirectory(tests)
endif()