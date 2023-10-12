#include <gtest/gtest.h>
#include "four.h"

TEST(Group_01, basic_test_set)
{
    Four num1, num2;

    ASSERT_TRUE(num1.to_string() == "0" && num2.to_string() == "0");

    num1 = "10";
    EXPECT_TRUE(num1.to_decimal() == 4);

    num2 = num2 + num1;
    EXPECT_TRUE(num2.to_string() == "10");

    EXPECT_TRUE(num1 == num2);
    EXPECT_FALSE(num1 > num2);
    EXPECT_FALSE(num1 < num2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}