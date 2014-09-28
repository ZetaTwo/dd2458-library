#include <cstdio>
#include <vector>
#include <iterator>
using namespace std;

#include "polymul.hpp"

#ifdef _WIN32
#define scanf scanf_s
#endif

int main() {
  //Number of test cases
  int T;
  scanf("%d", &T);

  //Perform each test case
  for (int i = 0; i < T; i++)
  {
    //Polynomial degrees
    int degree1, degree2;
    
    //Get polynomial 1
    scanf("%d", &degree1);
    vector<int> polynomial1(degree1+1);
    for (int j = 0; j <= degree1; j++)
    {
      scanf("%d", &polynomial1[j]);
    }

    //Get polynomial 2
    scanf("%d", &degree2);
    vector<int> polynomial2(degree2+1);
    for (int j = 0; j <= degree2; j++)
    {
      scanf("%d", &polynomial2[j]);
    }

    //Multiply
    vector<int> result = polymul<int>(polynomial1, polynomial2);

    //Output result
    printf("%lu\n", result.size() - 1);
    bool first = true;
    for (vector<int>::const_iterator coeff = result.cbegin(); coeff != result.cend(); coeff++)
    {
      if (first) {
        first = false;
      }
      else {
        printf(" ");
      }
      printf("%d", *coeff);
    }
    printf("\n");
  }

  return 0;
}