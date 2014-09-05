#include <gtest\gtest.h>

#include "../labb1-library/fenwick.hpp"

TEST(FenwickTree, Test1) {
  FenwickTree<int> tree1(4);
  tree1.add(0, 10);
  tree1.add(1, 10);
  tree1.add(2, 10);
  tree1.add(3, 10);

  EXPECT_EQ(10, tree1.sum(0, 0));
  EXPECT_EQ(10, tree1.sum(1, 1));
  EXPECT_EQ(10, tree1.sum(2, 2));
  EXPECT_EQ(10, tree1.sum(3, 3));

  EXPECT_EQ(20, tree1.sum(0, 1));
  EXPECT_EQ(20, tree1.sum(1, 2));
  EXPECT_EQ(20, tree1.sum(2, 3));

  EXPECT_EQ(30, tree1.sum(0, 2));
  EXPECT_EQ(30, tree1.sum(1, 3));

  EXPECT_EQ(40, tree1.sum(0, 3));
}