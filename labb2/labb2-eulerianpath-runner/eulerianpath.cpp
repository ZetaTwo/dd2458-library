// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

// http://en.wikipedia.org/wiki/Eulerian_path#Hierholzer.27s_algorithm

#include <iostream>
using namespace std;

#include "eulerianpath.hpp"

int main() {
  int N, M;
  while (cin >> N >> M) {
    if (N == 0 && M == 0) {
      break;
    }

    Graph<> graph(N);
    for (int m = 0; m < M; m++)
    {
      int u, v;
      cin >> u >> v;
      graph.add_edge(u, v);
    }



  }

  return 0;
}