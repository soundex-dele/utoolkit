cmake_minimum_required(VERSION 3.10)
project(utoolkit_logging)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGGING_SOURCES
    src/logger.cpp
)

add_library(utoolkit_logging STATIC ${LOGGING_SOURCES})

target_include_directories(utoolkit_logging
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(Threads REQUIRED)
target_link_libraries(utoolkit_logging Threads::Threads)

# 安装规则
install(TARGETS utoolkit_logging
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
option(LOGGING_BUILD_EXAMPLES "Build logging examples" OFF)
if(LOGGING_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# 测试
option(LOGGING_BUILD_TESTS "Build logging tests" OFF)
if(LOGGING_BUILD_TESTS)
    add_subdirectory(tests)
endif()