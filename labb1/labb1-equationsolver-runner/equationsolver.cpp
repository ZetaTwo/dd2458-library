#include <iostream>
#include <vector>
using namespace std;

#include "equationsolver.hpp"

int main() {
  size_t n;
  while (true) {
    //System size
    cin >> n;
    if (n == 0) {
      break;
    }

    //Input matrix
    vector<vector<long double> > A(n, vector<long double>(n, 0));
    for (size_t y = 0; y < n; y++)
    {
      for (size_t x = 0; x < n; x++)
      {
        cin >> A[y][x];
      }
    }

    //Input vector
    vector<long double> b(n, 0);
    vector<size_t> indices(n, 0);
    for (size_t x = 0; x < n; x++)
    {
      cin >> b[x];
      indices[x] = x;
    }

    //Solve system
    // result = equationsolver(A, b);
    EQUATIONSOLVER_RESULT result = equationsolver(A, b);

    //Output result
    bool first = true;
    switch (result)
    {
    case OK:
      for (size_t i = 0; i < b.size(); i++)
      {
        if (first) {
          first = false;
        }
        else {
          cout << " ";
        }
        cout << b[i];
      }
      break;
    case INCONSISTENT:
      cout << "inconsistent";
      break;
    case MULTIPLE:
      cout << "multiple";
      break;
    default:
      break;
    }
    cout << endl;
  }

  return 0;
}