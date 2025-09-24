#include <gtest/gtest.h>
#include <utoolkit/utils/time_utils.h>
#include <chrono>
#include <thread>

using namespace utoolkit::utils;

class TimeUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TimeUtilsTest, TimestampGeneration) {
    std::string timestamp = TimeUtils::get_current_timestamp();
    EXPECT_FALSE(timestamp.empty());
    EXPECT_TRUE(timestamp.find("-") != std::string::npos);
    EXPECT_TRUE(timestamp.find(":") != std::string::npos);
}

TEST_F(TimeUtilsTest, DateAndTime) {
    std::string date = TimeUtils::get_current_date();
    std::string time = TimeUtils::get_current_time();
    
    EXPECT_FALSE(date.empty());
    EXPECT_FALSE(time.empty());
    EXPECT_TRUE(date.find("-") != std::string::npos);
    EXPECT_TRUE(time.find(":") != std::string::npos);
}

TEST_F(TimeUtilsTest, EpochTimestamps) {
    int64_t ms = TimeUtils::get_timestamp_ms();
    int64_t us = TimeUtils::get_timestamp_us();
    
    EXPECT_GT(ms, 0);
    EXPECT_GT(us, 0);
    EXPECT_NEAR(ms * 1000, us, 1000);
}

TEST_F(TimeUtilsTest, TimerFunctionality) {
    TimeUtils::Timer timer;
    
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    timer.stop();
    
    auto elapsed_ms = timer.elapsed_ms();
    auto elapsed_us = timer.elapsed_us();
    
    EXPECT_GE(elapsed_ms.count(), 90);
    EXPECT_GE(elapsed_us.count(), 90000);
    EXPECT_NEAR(elapsed_ms.count() * 1000, elapsed_us.count(), 1000);
}

TEST_F(TimeUtilsTest, TimerReset) {
    TimeUtils::Timer timer;
    
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    timer.stop();
    
    auto elapsed1 = timer.elapsed_ms();
    
    timer.reset();
    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    timer.stop();
    
    auto elapsed2 = timer.elapsed_ms();
    
    EXPECT_GE(elapsed1.count(), 40);
    EXPECT_GE(elapsed2.count(), 20);
    EXPECT_LT(elapsed2.count(), elapsed1.count());
}

TEST_F(TimeUtilsTest, DurationFormatting) {
    std::string formatted = TimeUtils::format_duration(std::chrono::milliseconds(3661000));
    EXPECT_TRUE(formatted.find("1h") != std::string::npos);
    EXPECT_TRUE(formatted.find("1m") != std::string::npos);
    EXPECT_TRUE(formatted.find("1s") != std::string::npos);
}

TEST_F(TimeUtilsTest, DurationFormattingMicroseconds) {
    std::string formatted = TimeUtils::format_duration_us(std::chrono::microseconds(3661000000LL));
    EXPECT_TRUE(formatted.find("1h") != std::string::npos);
    EXPECT_TRUE(formatted.find("1m") != std::string::npos);
    EXPECT_TRUE(formatted.find("1s") != std::string::npos);
}

TEST_F(TimeUtilsTest, SleepFunctions) {
    auto start = TimeUtils::get_timestamp_ms();
    TimeUtils::sleep_ms(100);
    auto end = TimeUtils::get_timestamp_ms();
    
    EXPECT_GE(end - start, 90);
    EXPECT_LE(end - start, 200);
}