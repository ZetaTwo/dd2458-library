#include <gtest\gtest.h>

#include "../labb3-library/math.hpp"

TEST(Math, GCD) {
  EXPECT_EQ(1, gcd(3, 5));
  EXPECT_EQ(2, gcd(6, 10));
  EXPECT_EQ(3, gcd(9, 15));
}

TEST(Math, LCM) {
  EXPECT_EQ(15, lcm(3, 5));
  EXPECT_EQ(30, lcm(6, 10));
  EXPECT_EQ(45, lcm(9, 15));
}

TEST(Math, EGCD) {
  egcd_res<int> res = egcd(240, 46);
  EXPECT_EQ(2, res.gcd);
  EXPECT_EQ(res.gcd, res.coeff_a * 240 + res.coeff_b * 46);
}

TEST(Math, Inverse) {
  EXPECT_EQ(1000, inverse(998, 1000));
  EXPECT_EQ(999, inverse(999, 1000));
}