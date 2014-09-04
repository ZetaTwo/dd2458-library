#pragma once

#include <vector>
using std::vector;

class FenwickTree
{
public:
	FenwickTree(int N) {
		tree.resize(N);
	}

	// Increase index 'i' by 'delta'
	void add(int i, int delta) {
		for (; i < tree.size(); i |= i+1)
			tree[i] += delta;
	}

	// Returns sum of elements with from index 'left' to 'right'
	int getsum(int left, int right) {
		return sum(right) - sum(left-1);
	}

private:
	vector<int> tree;

	int sum(int index) {
		int sum = 0;
		while (index >= 0) {
			sum += tree[index];
			index &= index + 1;
			index--;
		}
		return sum;
	}
};
