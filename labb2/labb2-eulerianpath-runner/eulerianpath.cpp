// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

// http://en.wikipedia.org/wiki/Eulerian_path#Hierholzer.27s_algorithm

#include <iostream>
#include <vector>
using namespace std;

#include "eulerianpath.hpp"

int main() {
  int N, M;
  while (cin >> N >> M) {
    if (N == 0 && M == 0) {
      break;
    }

    EulerGraph graph(N);
    for (int m = 0; m < M; m++)
    {
      int u, v;
      cin >> u >> v;
      graph.add_edge(u, v);
    }

    vector<size_t> result = eulerianpath(graph);
    if (result.size() == 0) {
      cout << "Impossible" << endl;
    }
    else {
      for (auto e : result)
      {
        cout << e << " ";
      }
      cout << endl;
    }
  }

  return 0;
}