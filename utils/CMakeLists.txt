cmake_minimum_required(VERSION 3.10)
project(utoolkit_utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(UTILS_SOURCES
    src/string_utils.cpp
    src/time_utils.cpp
    src/file_utils.cpp
)

add_library(utoolkit_utils STATIC ${UTILS_SOURCES})

target_include_directories(utoolkit_utils
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(Threads REQUIRED)
target_link_libraries(utoolkit_utils Threads::Threads)

# 安装规则
install(TARGETS utoolkit_utils
    EXPORT utoolkit-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/utoolkit
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# 示例
option(UTILS_BUILD_EXAMPLES "Build utils examples" OFF)
if(UTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# 测试
if(UTOOLKIT_BUILD_TESTS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_subdirectory(tests)
endif()