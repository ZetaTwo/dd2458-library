// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
using namespace std;

#include "modular.hpp"

int main() {
  //Get test case
  long long N, T;
  while (cin >> N >> T) {
    if (N == 0 && T == 0) {
      break;
    }

    //For each operation
    while (T--) {

      //Get operands and operation
      long long a, b;
      char op;
      cin >> a >> op >> b;
      modulo<long long> am(a, N);
      modulo<long long> bm(b, N);

      //Perform calculation
      switch (op) {
      case '+':
        cout << (am + bm) << endl;
        break;
      case '-':
        cout << (am - bm) << endl;
        break;
      case '*':
        cout << (am * bm) << endl;
        break;
      case '/':
        try {
          cout << (am / bm) << endl;
        }
        catch (...) {
          cout << -1 << endl;
        }
        
        break;
      }
    }
  }

  return 0;
}