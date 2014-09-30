// Longest increasing subsequence (n log n implementation)
// -----------------------------------------
// Authors: Magnus Olsson  (magolsso@kth.se)
//          Calle Svensson (carlsven@kth.se)

#include <vector>

// Returns a vector of indices pointing to the elements in the longest sequence
std::vector<int> longest_seq(vector<int>& list)
{
  std::vector<int> indices;
  std::vector<int> p(list.size());

  if (list.empty()) return indices;

  indices.push_back(0);

  // If next element list[i] is greater than last element of
  // current longest subsequence list[indices.back()], just push it at back of "indices" and continue
  for (size_t i = 1; i < list.size(); i++) {
    if (list[indices.back()] < list[i]) {
      p[i] = indices.back();
      indices.push_back(i);
      continue;
    }

    // Binary search to find the smallest element referenced by b which is just bigger than list[i]
    // Note : Binary search is performed on indices (and not list).
    // Size of indeces is always <=k and hence contributes O(log k) to complexity.
    int low = 0;
    int hi = indices.size()-1;
    while (low < hi) {
      int mid = (low + hi) / 2;
      if (list[indices[mid]] < list[i])
        low = mid + 1;
      else
        hi = mid;
    }

    // Update indeces if new value is smaller than previously referenced value
    if (list[i] < list[indices[low]]) {
      if (low > 0)
        p[i] = indices[low-1];
      indices[low] = i;
    }
  }

  int j = indices.back();
  for (int i = indices.size()-1; i >= 0; i--) {
    indices[i] = j;
    j = p[j];
  }

  return indices;
}