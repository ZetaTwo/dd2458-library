#include <cstdio>
using namespace std;

#include "fenwick.hpp"

//iostream is too slow with this amount of input/output, use scanf/printf instead
//On windows, use secure version of scanf
#ifdef _WIN32
#define scanf scanf_s
#endif

int main() {
  int N, Q;
  scanf("%d %d\n", &N, &Q);
  
  FenwickTree<long long> tree(N);

  while (Q--)
  {
    char command;
    int param1, param2;

    scanf("%c", &command);
    
    //Modification
    if (command == '+') {
      scanf("%d %d\n", &param1, &param2);
      tree.add(param1, param2);
    }
    //Query
    else {
      scanf("%d\n", &param1);
      printf("%lld\n", tree.sum(0, param1 - 1));
    }
  }

  return 0;
}