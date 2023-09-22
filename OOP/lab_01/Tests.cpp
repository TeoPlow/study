#include <gtest/gtest.h>
#include "palindrom.h"

TEST(test_01, basic_test_set)
{
    ASSERT_FALSE(palindrom("qwerty"));
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(palindrom("aboba"));
}

TEST(test_03, basic_test_set)
{
    ASSERT_FALSE(palindrom("calcal"));
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(palindrom("10201"));
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(palindrom("QeWrWeQ"));
}

TEST(test_06, basic_test_set)
{
    ASSERT_TRUE(palindrom("a"));
}

TEST(test_07, basic_test_set)
{
    ASSERT_TRUE(palindrom("1"));
}

TEST(test_08, basic_test_set)
{
    ASSERT_FALSE(palindrom("111qwer111"));
}

TEST(test_09, basic_test_set)
{
    ASSERT_TRUE(palindrom("sssZZZsss"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}