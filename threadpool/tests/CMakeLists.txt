# threadpool模块测试

set(THREADPOOL_TEST_SOURCES
    test_threadpool.cpp
)

# 创建测试可执行文件
add_executable(threadpool_tests ${THREADPOOL_TEST_SOURCES})

# 链接库
target_link_libraries(threadpool_tests PRIVATE utoolkit_threadpool)

# 如果使用GoogleTest
if(TARGET GTest::gtest OR TARGET gtest)
    if(TARGET GTest::gtest)
        target_link_libraries(threadpool_tests PRIVATE GTest::gtest)
    else()
        target_link_libraries(threadpool_tests PRIVATE gtest)
    endif()
    
    # 添加测试
    add_test(NAME threadpool_tests COMMAND threadpool_tests)
endif()

# 设置测试属性
set_target_properties(threadpool_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)