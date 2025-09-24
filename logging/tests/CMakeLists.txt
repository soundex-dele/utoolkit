# logging模块测试

set(LOGGING_TEST_SOURCES
    test_logger.cpp
)

# 创建测试可执行文件
add_executable(logging_tests ${LOGGING_TEST_SOURCES})

# 链接库
target_link_libraries(logging_tests PRIVATE utoolkit_logging)

# 如果使用GoogleTest
if(TARGET GTest::gtest OR TARGET gtest)
    if(TARGET GTest::gtest)
        target_link_libraries(logging_tests PRIVATE GTest::gtest)
    else()
        target_link_libraries(logging_tests PRIVATE gtest)
    endif()
    
    # 添加测试
    add_test(NAME logging_tests COMMAND logging_tests)
endif()

# 设置测试属性
set_target_properties(logging_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)