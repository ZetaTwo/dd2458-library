#include <gtest\gtest.h>

#include "../labb3-library/rational.hpp"

TEST(Rational, Constructor) {
  rational<int> a(1, 2);
  
  EXPECT_EQ(1, a.getNumerator());
  EXPECT_EQ(2, a.getDenominator());
}

TEST(Rational, ConstructorNegative) {
  rational<int> a(-1, 2);

  EXPECT_EQ(-1, a.getNumerator());
  EXPECT_EQ(2, a.getDenominator());
}

TEST(Rational, ConstructorNegative2) {
  rational<int> a(1, -2);

  EXPECT_EQ(-1, a.getNumerator());
  EXPECT_EQ(2, a.getDenominator());
}

TEST(Rational, ConstructorNegative3) {
  rational<int> a(-1, -2);

  EXPECT_EQ(1, a.getNumerator());
  EXPECT_EQ(2, a.getDenominator());
}

TEST(Rational, Addition) {
  rational<int> a(1, 2);
  rational<int> b(3, 4);
  rational<int> d(5, 4);
  rational<int> c = a + b;

  EXPECT_EQ(d, c);
}

TEST(Rational, AdditionFail) {
  rational<int> a(1, 2);
  rational<int> b(1, 2);
  rational<int> d(3, 2);
  rational<int> c = a + b;

  EXPECT_NE(d, c);
}

TEST(Rational, AdditionInt) {
  rational<int> a(1, 2);
  rational<int> b(3, 2);
  rational<int> c = a + 1;
  rational<int> d = 1 + a;

  EXPECT_EQ(c, b);
  EXPECT_EQ(d, b);
}

TEST(Rational, Multiplication) {
  rational<int> a(1, 2);
  rational<int> b(3, 4);
  rational<int> d(3, 8);
  rational<int> c = a * b;

  EXPECT_EQ(d, c);
}

TEST(Rational, MultiplicationFail) {
  rational<int> a(1, 2);
  rational<int> b(1, 2);
  rational<int> d(1, 5);
  rational<int> c = a * b;

  EXPECT_NE(d, c);
}

TEST(Rational, MultiplicationInt) {
  rational<int> a(1, 2);
  rational<int> b(1, 1);
  rational<int> c = a * 2;
  rational<int> d = 2 * a;

  EXPECT_EQ(c, b);
  EXPECT_EQ(d, b);
}

TEST(Rational, Division) {
  rational<int> a(3, 8);
  rational<int> b(1, 2);
  rational<int> d(3, 4);
  rational<int> c = a / b;

  EXPECT_EQ(d, c);
}

TEST(Rational, DivisionFail) {
  rational<int> a(1, 2);
  rational<int> b(1, 2);
  rational<int> d(1, 2);
  rational<int> c = a / b;

  EXPECT_NE(d, c);
}

TEST(Rational, DivisionInt) {
  rational<int> a(1, 2);
  rational<int> b(1, 4);
  rational<int> c(4, 1);
  rational<int> d = a / 2;
  rational<int> e = 2 / a;

  EXPECT_EQ(d, b);
  EXPECT_EQ(e, c);
}

TEST(Rational, Compare) {
  rational<int> a(1, 2);
  rational<int> b(1, 2);
  rational<int> c(1, 3);

  EXPECT_EQ(b, a);
  EXPECT_NE(c, a);
}

TEST(Rational, CompareInt) {
  rational<int> a(2, 1);

  EXPECT_EQ(2, a);
  EXPECT_NE(3, a);
  EXPECT_EQ(a, 2);
  EXPECT_NE(a, 3);
}