// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
#include <vector>
using namespace std;

#include "math.hpp"

int main() {
	int T;
	cin >> T;
	while (T--) {
		vector<long long> moduli(2);
    vector<long long> remainder(2);
		cin >> remainder[0] >> moduli[0] >> remainder[1] >> moduli[1];

		cout << chineseremainder(remainder, moduli) << " " << lcm(moduli[0], moduli[1]) << endl;
	}

	return 0;
}