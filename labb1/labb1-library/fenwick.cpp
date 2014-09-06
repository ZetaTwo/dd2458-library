#include <iostream>
using namespace std;

#include "fenwick.hpp"

int main() {
  int N, Q;
  //cin >> N >> Q;
  scanf("%d %d\n", &N, &Q);
  
  FenwickTree<long long> tree(N);

  while (Q--)
  {
    char command;
    int param1, param2;

    //cin >> command;
    scanf("%c", &command);
    
    //Modification
    if (command == '+') {
      //cin >> param1 >> param2;
      scanf("%d %d\n", &param1, &param2);
      tree.add(param1, param2);
    }
    //Query
    else {
      //cin >> param1;
      scanf("%d\n", &param1);
      cout << tree.sum(0, param1 - 1) << endl;
    }
  }

  return 0;
}