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

    vector<point<long long> > points(n);
    for (size_t i = 0; i < n; i++) {
      cin >> points[i];
    }

    vector<point<long long> > hull = convex_hull<long long>(points.begin(), points.end());
    cout << hull.size() << endl;
    for (const auto& p : hull) {
      cout << p.getX() << " " << p.getY() << endl;
    }
  }


  return 0;
}