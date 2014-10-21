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

  vector<vector<int> > graph(N, vector<int>(N));
  vector<set<int>> out_edges(N);
  vector<vector<int> > flowGraph(N, std::vector<int>(N));
  //MaxFlowGraph graph(N);
  for (int m = 0; m < M; m++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u][v] = w;
    out_edges[u].insert(v);
    out_edges[v].insert(u);
    //graph.add_edge(u, v, { w, 0 });
  }

  //vector<MaxFlowEdge*> flow_graph;
  //int flow = maxflow(graph, S, T, flow_graph);
  int flow = fordFulkerson(graph, S, T, flowGraph, out_edges);
 
  int count = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (flowGraph[i][j] > 0) {
        count++;
      }
    }
  }
  cout << N << " " << flow << " " << count << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (flowGraph[i][j] > 0) {
        cout << i << " " << j << " " << flowGraph[i][j] << endl;
      }
    }
  }
  /*for (auto e : flow_graph)
  {
    cout << e->left->id << " " << e->right->id << " " << e->extra.flow << endl;
  }*/

  return 0;
}