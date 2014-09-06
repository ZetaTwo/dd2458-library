#pragma once

#include <vector>

template<typename T>
class FenwickTree {
public:
  FenwickTree(int size) {
    tree.resize(size);
  }

  void add(int i, T delta) {
    for (; i < (int)tree.size(); i |= i + 1)
      tree[i] += delta;
  }

  T sum(int left, int right) {
    return sum(right) - sum(left - 1);
  }

private:
  std::vector<T> tree;

  T sum(int index) {
    T sum = 0;

    while (index >= 0) {
      sum += tree[index];
      index &= index + 1;
      index--;
    }

    return sum;
  }
};