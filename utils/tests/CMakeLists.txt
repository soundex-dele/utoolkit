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

# 添加utils模块的测试
file(GLOB TEST_SOURCES "*.cpp")
add_executable(utils_tests ${TEST_SOURCES})
target_link_libraries(utils_tests 
    gtest 
    gtest_main 
    utoolkit_utils
)
target_compile_features(utils_tests PRIVATE cxx_std_17)
target_include_directories(utils_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)