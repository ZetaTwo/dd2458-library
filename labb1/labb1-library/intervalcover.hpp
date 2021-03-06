// Interval cover algorithm
// -----------------------------------------
// Authors: Magnus Olsson  (magolsso@kth.se)
//          Calle Svensson (carlsven@kth.se)

#include <vector>
#include <algorithm>

namespace intervalcover {
  //An interval covering [start, end]
  template<typename T>
  struct interval {
    T start;
    T end;
  };

  //Used internally to sort the indices of the intervals on increasing start order
  template<typename T>
  struct interval_indices_cmp {
    const std::vector<interval<T> >&intervals;

    interval_indices_cmp(const std::vector<interval<T> >&intervals) : intervals(intervals) {
    }

    bool operator()(const int left, const int right) {
      return intervals[left].start < intervals[right].start;
    }
  };

  //Given a list, intervals, and a target interval, target, calculates a minimum size subset of intervals which covers target and returns a list of indices to the intervals of that subset
  template<typename T>
  std::vector<size_t> cover(const interval<T>& target, const std::vector<interval<T> >& intervals) {
    //Create indices vector
    std::vector<size_t> indices(intervals.size());
    for (size_t i = 0; i < indices.size(); i++)
    {
      indices[i] = i;
    }

    //Sort indicies by start position
    std::sort(indices.begin(), indices.end(), interval_indices_cmp<T>(intervals));

    std::vector<size_t>::const_iterator scan_index = indices.begin();
    std::vector<size_t> result;
    T front = target.start;
    //While we still have interval to cover and there is stuff to pick from
    while ((result.size() == 0 || front < target.end) && scan_index != indices.end()) {
      
      //Pick interval that starts early enough and ends furthest away
      size_t candidate_index = *scan_index;
      if (intervals[*scan_index++].start <= front) {
        while (scan_index != indices.end() && intervals[*scan_index].start <= front) {
          if (intervals[*scan_index].end > intervals[candidate_index].end) {
            candidate_index = *scan_index;
          }
          scan_index++;
        }

        //Update remaining interval
        result.push_back(candidate_index);
        front = intervals[candidate_index].end;
      }
    }

    //Did we succeed?
    if (front < target.end) {
      return std::vector<size_t>();
    }
    else {
      return result;
    }
  }
}