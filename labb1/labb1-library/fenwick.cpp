#include <iostream>
using namespace std;

#include "fenwick.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  
  FenwickTree<long long> tree(N);

  while (Q--)
  {
    char command;
    int param1, param2;

    cin >> command;
    
    //Query
    if (command == '?') {
      cin >> param1;
      cout << tree.sum(0, param1 - 1) << endl;
    }
    //Modification
    else {
      cin >> param1 >> param2;
      tree.add(param1, param2);
    }
  }

  return 0;
}