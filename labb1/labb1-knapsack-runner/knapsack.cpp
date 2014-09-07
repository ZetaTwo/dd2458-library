#include <cstdio>
#include <vector>
using namespace std;

#include "knapsack.hpp"
using namespace knapsack;

#ifdef _WIN32
#define scanf scanf_s
#endif

int main() {
  //Input parameters
  double C;
  int n;

  //Continue while there are more test cases
  while (scanf("%lf %d\n", &C, &n) == 2) {
    //Read items
    vector<knapsack::item> items(n);
    for (size_t i = 0; i < (size_t)n; i++)
    {
      scanf("%d %d\n", &items[i].value, &items[i].weight);
    }

    //Perform dynamic programming knapsack
    vector<size_t> knapsack_indices = knapsack::knapsack(static_cast<weight_type>(C), items);

    //Output result
    printf("%d\n", knapsack_indices.size());
    bool first = true;
    for (vector<size_t>::const_iterator itr = knapsack_indices.begin(); itr != knapsack_indices.end(); itr++)
    {
      if (first) {
        first = false;
      }
      else {
        printf(" ");
      }
      printf("%d", *itr);
    }
    printf("\n");
  }

  return 0;
}