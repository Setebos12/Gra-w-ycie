#include <gtest/gtest.h>
#include "parser.h"

Parser constructParser(std::initializer_list<const char*> argsList) {
    std::vector<const char*> argv;
    argv.push_back("prog");
    argv.insert(argv.end(), argsList.begin(), argsList.end());
    return Parser(static_cast<int>(argv.size()), argv.data());
}

TEST(ParseTest, Flag) {
    auto parse{ constructParser({"-flag", "-flagb"})};
	EXPECT_TRUE(parse.getFlag("-flag"));
}

TEST(ParseTest, FlagRepeated) {
    auto parse{ constructParser({"-flag", "-flag"})};
    EXPECT_TRUE(parse.getFlag("-flag"));
}

TEST(ParseTest, FlagFalse) {
    auto parse{ constructParser({}) };
    EXPECT_FALSE(parse.getFlag("-flag"));
}

TEST(ParseTest, LastArgumentFlag) {
    auto parse{ constructParser({"-lastFlag"}) };
    EXPECT_TRUE(parse.getFlag("-lastFlag"));
}

TEST(ParseTest, FlagArg) {
    auto parse{ constructParser({"-n", "42", "-r", "43"})};
    auto result = parse.getArg<int>("-n");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 42);
}

TEST(ParseTest, FlagArgLast) {
    auto parse{ constructParser({"-n", "42"}) };
    auto result = parse.getArg<int>("-n");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 42);
}

TEST(ParseTest, FlagArgNoArg) {
    auto parse{ constructParser({"-n"}) };
    EXPECT_FALSE(parse.getArg<int>("-n").has_value());
}

TEST(ParseTest, FlagArgParse) {
    auto parse{ constructParser({"-n", "3.14"}) };
    auto result = parse.getArg<float>("-n");
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(result.value(), 3.14f);
}

TEST(ParseTest, FlagArgParseFail) {
    auto parse{ constructParser({"-n", "abc"}) };
    auto result = parse.getArg<float>("-n");
    ASSERT_FALSE(result.has_value());
}