#include <iostream>
using namespace std;

#include "fenwick.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;

  FenwickTree tree(N);

  for (int i = 0; i < Q; i++)
  {
    char command;
    int param1, param2;
    cin >> command;
    
    //Query
    if (command == '?') {
      cin >> param1;
      //Empty set
      if (param1 == 0) {
        cout << 0 << endl;
      }
      //Range
      else {
        cout << tree.getsum(0, param1 - 1) << endl;
      }
    }
    //Modification
    else {
      cin >> param1 >> param2;
      tree.add(param1, param2);
    }
  }

  return 0;
}