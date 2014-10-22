#include <iostream>
using namespace std;

#include "rational.hpp"

int main() {
  int N;
  cin >> N;
  while (N--) {
    long long a1, a2, b1, b2;
    char op;
    
    cin >> a1 >> a2 >> op >> b1 >> b2;
    rational<long long> a(a1, a2);
    rational<long long> b(b1, b2);

    switch (op) {
    case '+':
      a += b;
      break;
    case '-':
      a -= b;
      break;
    case '*':
      a *= b;
      break;
    case '/':
      a /= b;
      break;
    } 

    cout << a.getNumerator() << " / " << a.getDenominator() << endl;
  }

  return 0;
}