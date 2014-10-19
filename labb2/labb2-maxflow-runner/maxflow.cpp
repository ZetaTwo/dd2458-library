// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
#include <vector>
using namespace std;

#include "maxflow.hpp"

int main() {
  int N, M, S, T;
  cin >> N >> M >> S >> T;


  MaxFlowGraph graph(N);
  for (int m = 0; m < M; m++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    graph.add_edge(u, v, { w, 0 });
  }

  vector<MaxFlowEdge*> flow_graph;
  int flow = maxflow(graph, S, T, flow_graph);
  cout << N << " " << flow << " " << flow_graph.size() << endl; 
  for (auto e : flow_graph)
  {
    cout << e->left->id << " " << e->right->id << " " << e->extra.flow << endl;
  }

  return 0;
}