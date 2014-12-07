#include <gtest\gtest.h>

#include <vector>

#include "../labb4-library/point.hpp"

TEST(Point, On) {
  const point<int> a(-10, 0);
  const point<int> b(-5, 0);
  const point<int> c(0, 0);
  const point<int> d(5, 0);
  const point<int> e(10, 0);


  EXPECT_TRUE(on(c, b, d));
  EXPECT_TRUE(on(c, d, b));

  EXPECT_TRUE(on(b, a, b));
  EXPECT_TRUE(on(a, a, b));

  EXPECT_TRUE(on(b, a, c));
  EXPECT_TRUE(on(b, c, a));

  EXPECT_TRUE(on(b, a, d));
  EXPECT_TRUE(on(b, d, a));

  EXPECT_FALSE(on(a, b, c));
  EXPECT_FALSE(on(a, c, d));
}
