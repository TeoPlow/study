#include <gtest/gtest.h>
#include "four.h"

TEST(Tests, test1) {
    Four a("13");
    Four b("12");

    ASSERT_TRUE(a.to_string() == "13" && b.to_string() == "12");

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(a < b);

    EXPECT_TRUE(a.to_10() == 7);

    b = b + a;
    EXPECT_TRUE(b.to_string() == "31");

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a > b);
    EXPECT_TRUE(a < b);
}

TEST(Tests, test2) {
    Four a("103");
    Four b("2");

    ASSERT_TRUE(a.to_string() == "103" && b.to_string() == "2");

    EXPECT_TRUE(b.to_10() == 2);
    EXPECT_TRUE(a.to_10() == 19);

    a = a - b;
    EXPECT_TRUE(a.to_string() == "101");

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(a < b);
}

TEST(Tests, test3) {
    Four a("201021013");
    Four b("201021013");

    EXPECT_TRUE(a.to_10() == 135751);
    EXPECT_TRUE(b.to_10() == 135751);

    a = a - b;
    EXPECT_TRUE(a.to_string() == "0");

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a > b);
    EXPECT_TRUE(a < b);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}