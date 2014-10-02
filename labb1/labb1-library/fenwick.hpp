// Fenwick Tree implementation
// -----------------------------------------
// Authors: Magnus Olsson  (magolsso@kth.se)
//          Calle Svensson (carlsven@kth.se)

#pragma once

#include <algorithm>

template<typename T>
class FenwickTree {
public:
  //Create a Fenwick tree of given size
  FenwickTree(int size): size(size) {
    tree = new T[size];
    std::fill(tree, tree+size, 0);
  }

  ~FenwickTree() {
    delete[] tree;
  }

  // Increases value of i-th element by delta
  void add(int i, T delta) {
    for (; i < size; i |= i + 1)
      tree[i] += delta;
  }

  // Returns sum of elements with indexes left to right, inclusive
  T sum(int left, int right) {
    return sum(right) - sum(left - 1);
  }

private:
  T* tree;
  int size;

  // Calculates sum from index 0 to given input
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