// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
using namespace std;

#include "dijkstra.hpp"

int main() {
  //For each test case
  while (true) {

    //Get inputs
    int num_nodes, num_edges, num_queries, start_node;
    cin >> num_nodes >> num_edges >> num_queries >> start_node;
    if (num_nodes + num_edges + num_queries + start_node == 0) break;

    DijkstraTimeTableGraph graph(num_nodes);

    //Get edges
    for (int i = 0; i < num_edges; i++) {
      int u, v, t0, P, d;
      cin >> u >> v >> t0 >> P >> d;
      graph.add_edge(u, v, { t0, P, d });
    }

    //Calculate shortest path
    dijkstra(graph[start_node]);

    //Get queries
    for (int i = 0; i < num_queries; i++) {
      int q;
      cin >> q;
      int dist = graph[q]->extra.value;

      //Impossible
      if (dist == numeric_limits<int>::max()) {
        cout << "Impossible" << endl;

        //Print result
      }
      else {
#ifdef PRINT_PATH
        vector<Node*> path = get_path(nodes[q]);
        for (int i = 0; i < path.size(); i++) {
          cout << path[i]->id << (i < path.size() - 1 ? ", " : "\n");
        }
#else
        cout << dist << endl;
#endif
      }
    }
    cout << endl;
  }

  return 0;
}