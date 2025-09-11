# 包含ExternalProject模块
include(ExternalProject)

# 设置使用指定路径的NDK编译x86_64架构
# 在Windows上，确保路径使用正确的分隔符
if(NOT DEFINED ANDROID_NDK_PATH)
    # 在Windows上使用正确的路径分隔符
    if(WIN32)
        set(ANDROID_NDK_PATH "D:\\Android\\Sdk\\ndk\\27.0.12077973")
    else()
        set(ANDROID_NDK_PATH "D:\\Android\\Sdk\\ndk\\27.0.12077973")
    endif()
endif()

# 如果没有设置构建类型，默认为Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
set(THIRD_PARTY_DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/downloads CACHE PATH "Path to store downloaded third-party sources")

# 设置第三方依赖的安装目录
set(THIRD_PARTY_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install/${ANDROID_ABI} CACHE PATH "Path to install third-party libraries")

# 设置第三方依赖的构建目录
set(THIRD_PARTY_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build CACHE PATH "Path to build third-party libraries")

# 输出调试信息
message( "ANDROID_NDK_PATH: ${ANDROID_NDK_PATH}")
message( "ANDROID_ABI: ${ANDROID_ABI}")
message( "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message( "THIRD_PARTY_DOWNLOAD_DIR: ${THIRD_PARTY_DOWNLOAD_DIR}")
message( "THIRD_PARTY_INSTALL_DIR: ${THIRD_PARTY_INSTALL_DIR}")
message( "THIRD_PARTY_BUILD_DIR: ${THIRD_PARTY_BUILD_DIR}")

# 设置CMake工具链文件
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${ANDROID_NDK_PATH}/build/cmake/android.toolchain.cmake")
endif()

# 设置第三方依赖的下载目录
set(THIRD_PARTY_DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/downloads CACHE PATH "Path to store downloaded third-party sources")

# 设置第三方依赖的安装目录
set(THIRD_PARTY_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install/${ANDROID_ABI} CACHE PATH "Path to install third-party libraries")

# 设置第三方依赖的构建目录
set(THIRD_PARTY_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build CACHE PATH "Path to build third-party libraries")

# 创建目录的自定义目标
add_custom_target(CreateThirdPartyDirs
        COMMAND ${CMAKE_COMMAND} -E make_directory ${THIRD_PARTY_DOWNLOAD_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${THIRD_PARTY_INSTALL_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${THIRD_PARTY_BUILD_DIR}
        COMMENT "Creating third-party directories"
)

# 配置spdlog - 修复下载问题
ExternalProject_Add(
        spdlog
        PREFIX spdlog
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/spdlog
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_INSTALL_DIR}
        -DSPDLOG_BUILD_SHARED=ON
)


## 导出spdlog的安装信息
set(spdlog_FOUND TRUE CACHE BOOL "spdlog library found")
set(spdlog_INCLUDE_DIRS ${THIRD_PARTY_INSTALL_DIR}/include CACHE PATH "spdlog include directories")
set(spdlog_LIBRARY_DIRS ${THIRD_PARTY_INSTALL_DIR}/lib CACHE PATH "spdlog library directories")
set(spdlog_LIBRARIES spdlog::spdlog CACHE STRING "spdlog libraries")

## 添加spdlog的接口库，方便其他目标链接
add_library(spdlog_interface INTERFACE)
add_dependencies(spdlog_interface spdlog)
# 设置接口库的包含目录
set_target_properties(spdlog_interface PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${spdlog_INCLUDE_DIRS}
        INTERFACE_LINK_LIBRARIES ${spdlog_LIBRARY_DIRS}/libspdlog.so
)

