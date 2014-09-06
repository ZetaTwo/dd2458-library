#include <iostream>
using namespace std;

#include "intervalcover.hpp"
using namespace intervalcover;

typedef long double value_type;

int main() {
  //Input parameters
  interval<value_type> target;
  int n;

  //Run test cases until end of input
  while (cin >> target.start >> target.end >> n) {
    //Read intervals
    vector<interval<value_type> > intervals;
    for (int i = 0; i < n; i++)
    {
      value_type start, end;
      cin >> start >> end;
      intervals.push_back({ start, end });
    }

    //Process
    vector<size_t> cover_indices = cover(target, intervals);

    //Output answer
    if (cover_indices.size() > 0) {
      cout << cover_indices.size() << endl;
      bool first = true;
      for (vector<size_t>::const_iterator itr = cover_indices.begin(); itr != cover_indices.end(); itr++)
      {
        if (first) {
          first = false;
        }
        else {
          cout << " ";
        }
        cout << *itr;
      }
      cout << endl;
    }
    else {
      cout << "impossible" << endl;
    }
  }

  return 0;
}