#include <iostream>
using namespace std;

#include "../labb1-library/fenwick.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;

  FenwickTree tree(N);

  for (int i = 0; i < Q; i++)
  {
    char command;
    int param1, param2;
    cin >> command;
    
    switch (command)
    {
    case '?':
      cin >> param1;
      if (param1 == 0) {
        cout << 0 << endl;
      }
      else {
        cout << tree.getsum(0, param1-1) << endl;
      }
      break;
    case '+':
      cin >> param1 >> param2;
      tree.add(param1, param2);
    default:
      break;
    }
  }

  return 0;
}