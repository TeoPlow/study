#include <gtest/gtest.h>
#include "palindrom.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(palindrom("qwerty")== false);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(palindrom("aboba")== true);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(palindrom("calcal")== false);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(palindrom("10201")== true);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(palindrom("QeWrWeQ")== true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}