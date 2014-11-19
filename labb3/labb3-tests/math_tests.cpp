#include <gtest\gtest.h>

#include <vector>

#include "../labb3-library/math.hpp"

TEST(Math, GCD) {
  EXPECT_EQ(1, gcd(3, 5));
  EXPECT_EQ(2, gcd(6, 10));
  EXPECT_EQ(3, gcd(9, 15));
}

TEST(Math, GCD_LIST) {
  std::vector<int> numbers = { 6, 9, 12, 15 };
  EXPECT_EQ(3, gcd(numbers));

  numbers = { 2, 4, 6, 8 };
  EXPECT_EQ(2, gcd(numbers));
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

TEST(Math, CRT) {
  std::vector<int> remainders = { 1, 2 };
  std::vector<int> moduli = { 2, 3 };
  EXPECT_EQ(5, chineseremainder(remainders, moduli));

  remainders = { 151, 57 };
  moduli = { 783, 278 };
  EXPECT_EQ(31471, chineseremainder(remainders, moduli));
}

TEST(Math, CRT_Fail) {
  std::vector<int> remainders = { 1, 2 };
  std::vector<int> moduli = { 3, 3 };
  EXPECT_EQ(0, chineseremainder(remainders, moduli));

}

TEST(Math, CRT_General) {
  std::vector<int> remainders = { 10000, 9000 };
  std::vector<int> moduli = { 23000, 23000 };

  int res = generalchineseremainder(remainders, moduli);

  remainders = { 10000, 10000 };
  moduli = { 23000, 23000 };

  remainders = { 1234, 746 };
  moduli = { 2000, 2002 };
}