// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
#include <vector>
using namespace std;

#include "kruskal.hpp"

int main() {
  int N, M;
  while (cin >> N >> M) {
    if (N == 0 && M == 0) {
      break;
    }

    KruskalGraph graph(N);
    for (int m = 0; m < M; m++)
    {
      int u, v, w;
      cin >> u >> v >> w;

      if (v < u) {
        std::swap(u, v);
      }
      
      graph.add_edge(u, v, { w });
    }

    vector<KruskalEdge*> result = kruskal(graph);

    if (graph.getSize() > 1 && result.size() == 0) {
      cout << "Impossible" << endl;
    }
    else {
      long sum = 0;
      for (auto e : result) {
        sum += e->extra.weight;
      }
      cout << sum << endl;
      for (auto e : result) {
        cout << e->left->id << " " << e->right->id << endl;
      }
    }
  }

  return 0;
}