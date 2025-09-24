#include <gtest/gtest.h>
#include "utoolkit/logging/logger.h"

TEST(LoggerTest, BasicTest) {
    // 基本测试占位符
    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}