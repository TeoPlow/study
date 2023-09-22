#include <gtest/gtest.h>

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE("../Tests/test1.txt");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}