#include <vector>
#include <algorithm>

namespace knapsack {
  typedef int weight_type;
  typedef int value_type;

  struct item {
    value_type value;
    weight_type weight;
  };

  std::vector<size_t> knapsack(weight_type capacity, const std::vector<item>& items) {
    std::vector<std::vector<value_type> > knapsack(items.size(), vector<int>(capacity+1, 0));

    //Calculate dynprog table
    for (size_t c = 1; c <= capacity; c++)
    {
      for (size_t i = 0; i < items.size(); i++) {
        //Multiple items branch
        if (i > 0) {
          knapsack[i][c] = knapsack[i - 1][c];
          if (items[i].weight <= c) {
            value_type candidate_value = knapsack[i - 1][c - items[i].weight] + items[i].value;
            if (candidate_value > knapsack[i][c]) {
              knapsack[i][c] = candidate_value;
            }
          }
        }
        //Base values branch
        else {
          knapsack[i][c] = 0;
          if (items[i].weight <= c) {
            knapsack[i][c] = items[i].value;
          }
        }
      }
    }

    //Backtrack which items used
    weight_type it = items.size() - 1;
    weight_type ca = capacity;
    vector<size_t> result;
    while (ca > 0 && it >= 0)
    {
      if (ca - items[it].weight >= 0 && knapsack[it][ca] - items[it].value == knapsack[it][ca - items[it].weight]) {
        result.push_back(it);
        ca -= items[it].weight;
      }
      else {
        it--;
      }
    }
    std::reverse(result.begin(), result.end());

    return result;
  }
}