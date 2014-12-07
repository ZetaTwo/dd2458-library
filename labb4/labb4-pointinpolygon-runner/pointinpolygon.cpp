// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#include "point.hpp"

int main() {
  size_t n;
  while (cin >> n) {
    if (n == 0) break;

    vector<point<long long> > polygon(n);
    for (size_t i = 0; i < n; i++) {
      cin >> polygon[i];
    }

    size_t m;
    cin >> m;
    while (m--) {
      point<long long> p;
      cin >> p;
      switch (inside_poly(p, polygon.begin(), polygon.end())) {
      case -1:
        cout << "out";
        break;
      case 0:
        cout << "on";
        break;
      case 1:
        cout << "in";
        break;
      default:
        break;
      }
      cout << endl;
    }
  }


  return 0;
}