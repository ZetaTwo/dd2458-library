#include <cstdio>
#include <vector>
using namespace std;

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
    //Polynomial data
    int degree1, degree2;
    vector<int> polynomial1, polynomial2;
    
    //Get polynomial 1
    scanf("%d", &degree1);
    for (int j = 0; j < degree1; j++)
    {
      int coeff;
      scanf("%d", &coeff);
      polynomial1.push_back(coeff);
    }

    //Get polynomial 2
    scanf("%d", &degree2);
    for (int j = 0; j < degree2; j++)
    {
      int coeff;
      scanf("%d", &coeff);
      polynomial1.push_back(coeff);
    }

    //Multiply
    vector<int> result;
    //vector<int> result = polymul(polynomial1, polynomial2);

    //Output result
    printf("%d\n", result.size());
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