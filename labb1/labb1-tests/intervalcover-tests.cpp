#include <gtest\gtest.h>

#include <vector>
using namespace std;

#include "../labb1-library/intervalcover.hpp"
using namespace intervalcover;

TEST(IntervalCover, ZeroInterval) {
  interval<double> target = { 0.0, 0.0 };
  vector<interval<double> > intervals;
  intervals.push_back({ 0.0, 0.0 });

  vector<size_t> cover_indices = cover(target, intervals);
  EXPECT_EQ(1, cover_indices.size());
  EXPECT_EQ(0, cover_indices[0]);
}

TEST(IntervalCover, ZeroIntervalNegative) {
  interval<double> target = { 1.0, 1.0 };
  vector<interval<double> > intervals;
  intervals.push_back({ 0.0, 0.0 });

  vector<size_t> cover_indices = cover(target, intervals);
  EXPECT_EQ(0, cover_indices.size());
}


TEST(IntervalCover, SampleTest1) {
  interval<double> target = { -0.5, 1 };
  vector<interval<double> > intervals;
  intervals.push_back({ -0.9, -0.1 });
  intervals.push_back({ -0.2, 2 });
  intervals.push_back({ -0.7, 1 });

  vector<size_t> cover_indices = cover(target, intervals);
  EXPECT_EQ(1, cover_indices.size());
  EXPECT_EQ(2, cover_indices[0]);
}

TEST(IntervalCover, SampleTest2) {
  interval<double> target = { -0, 1 };
  vector<interval<double> > intervals;
  intervals.push_back({ 0, 0.25 });
  intervals.push_back({ 0.25, 0.75 });
  intervals.push_back({ 0.75, 0.999 });

  vector<size_t> cover_indices = cover(target, intervals);
  EXPECT_EQ(0, cover_indices.size());
}

TEST(IntervalCover, SampleTest3) {
  interval<double> target = { -0, 1 };
  vector<interval<double> > intervals;
  intervals.push_back({ 0, 0.25 });
  intervals.push_back({ 0.25, 0.75 });
  intervals.push_back({ 0.75, 1 });

  vector<size_t> cover_indices = cover(target, intervals);
  EXPECT_EQ(3, cover_indices.size());
  EXPECT_EQ(0, cover_indices[0]);
  EXPECT_EQ(1, cover_indices[1]);
  EXPECT_EQ(2, cover_indices[2]);
}

