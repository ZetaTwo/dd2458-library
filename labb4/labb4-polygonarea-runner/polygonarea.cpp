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

    cout << fixed << setprecision(1);
    double area = polygon_area<double>(points.begin(), points.end());
    if (area < 0) {
      cout << "CCW " << -area;
    }
    else {
      cout << "CW " << area;
    }
    cout << endl;
  }


  return 0;
}