#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

void longest_seq(vector<int> &list)
{
	vector<int> indexes;
	vector<int> p(list.size());

	if (list.empty()) return;

	indexes.push_back(0);

	for (int i = 1; i < list.size(); i++) {
		if (list[indexes.back()] < list[i]) {
			p[i] = indexes.back();
			indexes.push_back(i);
			continue;
		}

		int low = 0;
		int hi = indexes.size()-1;
		while (low < hi) {
			int mid = (low + hi) / 2;
			if (list[indexes[mid]] < list[i])
				low = mid+1;
			else
				hi = mid;
		}

		if (list[i] < list[indexes[low]]) {
			if (low > 0)
				p[i] = indexes[low-1];
			indexes[low] = i;
		}
	}

	int j = indexes.back();
	for (int i = indexes.size()-1; i >= 0; i--) {
		indexes[i] = j;
		j = p[j];
	}

	cout << indexes.size() << endl;

	for(auto x : indexes)
		cout << x << " ";
	cout << endl;
}

int main() {
	int num_digits;
	while (cin >> num_digits) {

		vector<int> v(num_digits);
		for (int i = 0; i < num_digits; i++) {
			cin >> v[i];
		}
		longest_seq(v);
	}
}
