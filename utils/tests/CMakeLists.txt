find_package(GTest QUIET)

if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
    
    set(GTEST_LIBRARIES gtest)
    set(GTEST_MAIN_LIBRARIES gtest_main)
endif()

# 添加各个模块的测试
add_subdirectory(${CMAKE_SOURCE_DIR}/logging/cmake ${CMAKE_BINARY_DIR}/logging_tests)
add_subdirectory(${CMAKE_SOURCE_DIR}/threadpool/cmake ${CMAKE_BINARY_DIR}/threadpool_tests)
add_subdirectory(${CMAKE_SOURCE_DIR}/utils/cmake ${CMAKE_BINARY_DIR}/utils_tests)