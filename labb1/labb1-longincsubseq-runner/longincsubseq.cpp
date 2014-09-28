#include <vector>
#include <iostream>
using namespace std;

#include "longincsubseq.hpp"

int main() {
	int num_digits;
	while (cin >> num_digits) {

		vector<int> v(num_digits);
		for (int i = 0; i < num_digits; i++) {
			cin >> v[i];
		}

    vector<int> indicies = longest_seq(v);

    cout << indicies.size() << endl;

    for (auto x : indicies)
      cout << x << " ";
    cout << endl;
	}
}
