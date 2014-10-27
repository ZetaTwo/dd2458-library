// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
#include <vector>
using namespace std;

#include "primesieve.hpp"

int main() {
  int n, q;
  cin >> n >> q;
  primesieve<int> primes(n);
  cout << primes.count() << endl;
  while (q--) {
    int x;
    cin >> x; x--;
    cout << primes.isprime(x) << endl;
  }

  return 0;
}