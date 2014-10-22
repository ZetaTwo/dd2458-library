#include <gtest\gtest.h>

#include "../labb3-library/modular.hpp"

TEST(Modular, Division) {
  modulo<int> a(1, 1000);

  EXPECT_EQ(999, a / 999);
  EXPECT_THROW({
    a / 998;
  }, std::invalid_argument);
}

TEST(Modular, Addition) {
  modulo<int> a(10, 13);
  modulo<int> b(1, 13);

  EXPECT_EQ(11, a + b);

  EXPECT_EQ(7, a + 10);
  EXPECT_EQ(11, a + 1);
  EXPECT_EQ(1, b + 13);
  EXPECT_EQ(11, b + 10);

  EXPECT_EQ(7, 10 + a);
  EXPECT_EQ(11, 1 + a);
  EXPECT_EQ(1, 13 + b);
  EXPECT_EQ(11, 10 + b);

  EXPECT_EQ(0, a + (-10));
  EXPECT_EQ(9, a + (-1));
  EXPECT_EQ(1, b + (-13));
  EXPECT_EQ(4, b + (-10));
}

TEST(Modular, Subtraction) {
  modulo<int> a(10, 13);
  modulo<int> b(1, 13);

  EXPECT_EQ(9, a - b);
  EXPECT_EQ(4, b - a);

  EXPECT_EQ(0, a - 10);
  EXPECT_EQ(12, a - 11);
  EXPECT_EQ(0, b - 1);
  EXPECT_EQ(12, b - 2);

  EXPECT_EQ(0, 10 - a);
  EXPECT_EQ(4, 1 - a);
  EXPECT_EQ(12, 13 - b);
  EXPECT_EQ(9, 10 - b);

  EXPECT_EQ(7, a - (-10));
  EXPECT_EQ(11, a - (-1));
  EXPECT_EQ(1, b - (-13));
  EXPECT_EQ(11, b - (-10));
}

TEST(Modular, Multiplication) {
  modulo<int> a(10, 13);
  modulo<int> b(1, 13);

  EXPECT_EQ(9, a * 10);
  EXPECT_EQ(6, a * 11);
  EXPECT_EQ(1, b * 1);
  EXPECT_EQ(2, b * 2);

  EXPECT_EQ(9, 10 * a);
  EXPECT_EQ(10, 1 * a);
  EXPECT_EQ(0, 13 * b);
  EXPECT_EQ(10, 10 * b);

  EXPECT_EQ(4, a * (-10));
  EXPECT_EQ(3, a * (-1));
  EXPECT_EQ(0, b * (-13));
  EXPECT_EQ(3, b * (-10));
}