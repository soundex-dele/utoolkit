#include <gtest/gtest.h>
#include <utoolkit/utils/string_utils.h>

using namespace utoolkit::utils;

class StringUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(StringUtilsTest, Trim) {
    EXPECT_EQ(StringUtils::trim("  hello  "), "hello");
    EXPECT_EQ(StringUtils::trim("\t\nhello\r\n"), "hello");
    EXPECT_EQ(StringUtils::trim("hello"), "hello");
    EXPECT_EQ(StringUtils::trim(""), "");
}

TEST_F(StringUtilsTest, TrimLeft) {
    EXPECT_EQ(StringUtils::trim_left("  hello"), "hello");
    EXPECT_EQ(StringUtils::trim_left("hello  "), "hello  ");
    EXPECT_EQ(StringUtils::trim_left("hello"), "hello");
}

TEST_F(StringUtilsTest, TrimRight) {
    EXPECT_EQ(StringUtils::trim_right("hello  "), "hello");
    EXPECT_EQ(StringUtils::trim_right("  hello"), "  hello");
    EXPECT_EQ(StringUtils::trim_right("hello"), "hello");
}

TEST_F(StringUtilsTest, CaseConversion) {
    EXPECT_EQ(StringUtils::to_lower("HELLO World"), "hello world");
    EXPECT_EQ(StringUtils::to_upper("hello world"), "HELLO WORLD");
}

TEST_F(StringUtilsTest, StartsWith) {
    EXPECT_TRUE(StringUtils::starts_with("hello world", "hello"));
    EXPECT_FALSE(StringUtils::starts_with("hello world", "world"));
    EXPECT_TRUE(StringUtils::starts_with("hello", "hello"));
    EXPECT_FALSE(StringUtils::starts_with("hello", "hello world"));
}

TEST_F(StringUtilsTest, EndsWith) {
    EXPECT_TRUE(StringUtils::ends_with("hello world", "world"));
    EXPECT_FALSE(StringUtils::ends_with("hello world", "hello"));
    EXPECT_TRUE(StringUtils::ends_with("hello", "hello"));
    EXPECT_FALSE(StringUtils::ends_with("hello", "hello world"));
}

TEST_F(StringUtilsTest, Split) {
    std::vector<std::string> result = StringUtils::split("a,b,c", ',');
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
    
    result = StringUtils::split("hello world", " ");
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
}

TEST_F(StringUtilsTest, Join) {
    std::vector<std::string> parts = {"a", "b", "c"};
    EXPECT_EQ(StringUtils::join(parts, ","), "a,b,c");
    EXPECT_EQ(StringUtils::join(parts, " - "), "a - b - c");
    
    std::vector<std::string> empty;
    EXPECT_EQ(StringUtils::join(empty, ","), "");
}

TEST_F(StringUtilsTest, Replace) {
    EXPECT_EQ(StringUtils::replace("hello world", "world", "C++"), "hello C++");
    EXPECT_EQ(StringUtils::replace("hello world", "foo", "bar"), "hello world");
}

TEST_F(StringUtilsTest, ReplaceAll) {
    EXPECT_EQ(StringUtils::replace_all("hello hello hello", "hello", "hi"), "hi hi hi");
    EXPECT_EQ(StringUtils::replace_all("hello world", "foo", "bar"), "hello world");
}

TEST_F(StringUtilsTest, Contains) {
    EXPECT_TRUE(StringUtils::contains("hello world", "world"));
    EXPECT_FALSE(StringUtils::contains("hello world", "foo"));
}

TEST_F(StringUtilsTest, Substring) {
    EXPECT_EQ(StringUtils::substring("hello world", 6), "world");
    EXPECT_EQ(StringUtils::substring("hello world", 0, 5), "hello");
    EXPECT_EQ(StringUtils::substring("hello", 10), "");
}

TEST_F(StringUtilsTest, TypeConversion) {
    EXPECT_EQ(StringUtils::to_int("42"), 42);
    EXPECT_EQ(StringUtils::to_double("3.14"), 3.14);
    EXPECT_EQ(StringUtils::to_long("123456789"), 123456789L);
    EXPECT_TRUE(StringUtils::to_bool("true"));
    EXPECT_TRUE(StringUtils::to_bool("1"));
    EXPECT_FALSE(StringUtils::to_bool("false"));
    EXPECT_FALSE(StringUtils::to_bool("0"));
}

TEST_F(StringUtilsTest, FromTypeConversion) {
    EXPECT_EQ(StringUtils::from_int(42), "42");
    EXPECT_EQ(StringUtils::from_double(3.14), "3.14");
    EXPECT_EQ(StringUtils::from_long(123456789L), "123456789");
    EXPECT_EQ(StringUtils::from_bool(true), "true");
    EXPECT_EQ(StringUtils::from_bool(false), "false");
}

TEST_F(StringUtilsTest, TypeChecking) {
    EXPECT_TRUE(StringUtils::is_integer("42"));
    EXPECT_FALSE(StringUtils::is_integer("42.5"));
    EXPECT_FALSE(StringUtils::is_integer("abc"));
    
    EXPECT_TRUE(StringUtils::is_float("3.14"));
    EXPECT_TRUE(StringUtils::is_float("42"));
    EXPECT_FALSE(StringUtils::is_float("abc"));
    
    EXPECT_TRUE(StringUtils::is_numeric("42"));
    EXPECT_TRUE(StringUtils::is_numeric("3.14"));
    EXPECT_FALSE(StringUtils::is_numeric("abc"));
}

TEST_F(StringUtilsTest, Format) {
    std::string formatted = StringUtils::format("Hello %s, number %d", "world", 42);
    EXPECT_EQ(formatted, "Hello world, number 42");
}

TEST_F(StringUtilsTest, Repeat) {
    EXPECT_EQ(StringUtils::repeat("a", 5), "aaaaa");
    EXPECT_EQ(StringUtils::repeat("hello", 2), "hellohello");
    EXPECT_EQ(StringUtils::repeat("test", 0), "");
}

TEST_F(StringUtilsTest, Padding) {
    EXPECT_EQ(StringUtils::pad_left("hello", 10), "     hello");
    EXPECT_EQ(StringUtils::pad_left("hello", 10, '*'), "*****hello");
    EXPECT_EQ(StringUtils::pad_right("hello", 10), "hello     ");
    EXPECT_EQ(StringUtils::pad_right("hello", 10, '*'), "hello*****");
    
    EXPECT_EQ(StringUtils::pad_left("hello", 3), "hello");
    EXPECT_EQ(StringUtils::pad_right("hello", 3), "hello");
}