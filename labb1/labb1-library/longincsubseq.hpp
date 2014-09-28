#include <vector>

std::vector<int> longest_seq(vector<int> &list)
{
  std::vector<int> indices;
  std::vector<int> p(list.size());

  if (list.empty()) return indices;

  indices.push_back(0);

  for (size_t i = 1; i < list.size(); i++) {
    if (list[indices.back()] < list[i]) {
      p[i] = indices.back();
      indices.push_back(i);
      continue;
    }

    int low = 0;
    int hi = indices.size() - 1;
    while (low < hi) {
      int mid = (low + hi) / 2;
      if (list[indices[mid]] < list[i])
        low = mid + 1;
      else
        hi = mid;
    }

    if (list[i] < list[indices[low]]) {
      if (low > 0)
        p[i] = indices[low - 1];
      indices[low] = i;
    }
  }

  int j = indices.back();
  for (int i = indices.size() - 1; i >= 0; i--) {
    indices[i] = j;
    j = p[j];
  }

  return indices;
}