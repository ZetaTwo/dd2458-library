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
    std::vector<std::vector<value_type> > knapsack(items.size()+1, vector<int>(capacity+1, 0));

    //Calculate dynprog table
    for (weight_type c = 1; c <= capacity; c++)
    {
      for (size_t i = 1; i <= items.size(); i++) {
        knapsack[i][c] = knapsack[i - 1][c];
        if (items[i-1].weight <= c) {
          value_type candidate_value = knapsack[i - 1][c - items[i-1].weight] + items[i-1].value;
          if (candidate_value > knapsack[i][c]) {
            knapsack[i][c] = candidate_value;
          }
        }
      }
    }

    //Backtrack which items used
    weight_type ca = capacity;
    vector<size_t> result;
    for (int i = items.size()-1; i >= 0 && ca >= 0; i--)
    {
      if (ca - items[i].weight >= 0 && knapsack[i+1][ca] - items[i].value == knapsack[i+1][ca - items[i].weight]) {
        result.push_back(i);
        ca -= items[i].weight;
      }
    }
    std::reverse(result.begin(), result.end());

    return result;
  }
}