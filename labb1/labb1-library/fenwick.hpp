// Fenwick Tree implementation
// -----------------------------------------
// Authors: Magnus Olsson  (magolsso@kth.se)
//          Calle Svensson (carlsven@kth.se)

#pragma once

template<typename T>
class FenwickTree {
public:
  FenwickTree(int size): size(size) {
    tree = new T[size];
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