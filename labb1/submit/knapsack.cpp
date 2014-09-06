#include <iostream>
using namespace std;

#include "knapsack.hpp"
using namespace knapsack;

int main() {
  //Input parameters
  double C;
  int n;

  //Continue while there are more test cases
  while (cin >> C >> n) {
    //Read items
    vector<knapsack::item> items;
    for (size_t i = 0; i < n; i++)
    {
      value_type value;
      weight_type weight;
      cin >> value >> weight;
      items.push_back({ value, weight });
    }

    //Perform dynamic programming knapsack
    vector<size_t> knapsack_indices = knapsack::knapsack(C, items);

    //Output result
    cout << knapsack_indices.size() << endl;
    if (knapsack_indices.size() > 0) {
      bool first = true;
      for (vector<size_t>::const_iterator itr = knapsack_indices.begin(); itr != knapsack_indices.end(); itr++)
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
  }

  return 0;
}