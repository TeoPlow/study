#include <gtest/gtest.h>
#include "figure.h"
#include "square.h"
#include "rectangle.h"
#include "trapeze.h"
#include "array.h"

// Тесты для класса Square
TEST(Square, EmptyConstructor) {
    Square s;
    EXPECT_DOUBLE_EQ(s.area(), 0.0);
    EXPECT_EQ(s.center(), std::make_pair(0.0, 0.0));
}

TEST(Square, VectorConstructor) {
    std::vector<double> x = {0.0, 10.0, 0.0, 10.0};
    std::vector<double> y = {0.0, 0.0, 10.0, 10.0};
    Square s(x, y);
    EXPECT_DOUBLE_EQ(s.area(), 100.0);
    EXPECT_EQ(s.center(), std::make_pair(5.0, 5.0));
}

// Тесты для класса Rectangle
TEST(Rectangle, EmptyConstructor) {
    Rectangle r;
    EXPECT_DOUBLE_EQ(r.area(), 0.0);
    EXPECT_EQ(r.center(), std::make_pair(0.0, 0.0));
}

TEST(Rectangle, VectorConstructor) {
    std::vector<double> x = {0.0, 10.0, 0.0, 10.0};
    std::vector<double> y = {0.0, 0.0, 5.0, 5.0};
    Rectangle r(x, y);
    EXPECT_DOUBLE_EQ(r.area(), 50.0);
    EXPECT_EQ(r.center(), std::make_pair(5.0, 2.5));
}

// Тесты для класса Trapeze
TEST(Trapeze, EmptyConstructor) {
    Trapeze t;
    EXPECT_DOUBLE_EQ(t.area(), 0.0);
    EXPECT_EQ(t.center(), std::make_pair(0.0, 0.0));
}

/*---------------------------НЕРАБОТАЕТ------------------------------*/
TEST(Trapeze, VectorConstructor) {
    std::vector<double> x = {0.0, 10.0, 0.0, 5.0};
    std::vector<double> y = {0.0, 0.0, 5.0, 5.0};
    Trapeze t(x, y);
    EXPECT_DOUBLE_EQ(t.area(), 50.0);
    EXPECT_EQ(t.center(), std::make_pair(3.75, 2.5));
}

// Тесты для класса Array
TEST(Array, EmptyConstructor) {
    Array a;
    EXPECT_EQ(a.get_size(), 10);
    for (size_t i = 0; i < a.get_size(); ++i) {
        EXPECT_EQ(a[i], nullptr);
    }
}

TEST(Array, SizeConstructor) {
    Array a(15);
    EXPECT_EQ(a.get_size(), 15);
    for (size_t i = 0; i < a.get_size(); ++i) {
        EXPECT_EQ(a[i], nullptr);
    }
}



/*---------------------------НЕРАБОТАЕТ------------------------------*/
TEST(Square, AssignmentOperator) {
    std::vector<double> x1 = {0.0, 10.0, 0.0, 10.0};
    std::vector<double> y1 = {0.0, 0.0, 10.0, 10.0};
    Square t1(x1, y1);
    
    std::vector<double> x2 = {0.0, 5.0, 0.0, 5.0};
    std::vector<double> y2 = {0.0, 0.0, 5.0, 5.0};
    Square t2(x2, y2);

    t2 = t1;

    EXPECT_DOUBLE_EQ(t2.area(), 50.0);
    EXPECT_NEAR(t2.center().first, 3.33333, 0.00001);
    EXPECT_NEAR(t2.center().second, 3.33333, 0.00001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}