// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
#include <vector>
using namespace std;

#include "floydwarshall.hpp"

// Do we want to show the calculated path?
// #define PRINT_PATH

int main() {
  //For each test case
  while (true) {

    //Get inputs
    int num_nodes, num_edges, num_queries;
    cin >> num_nodes >> num_edges >> num_queries;
    if (num_nodes + num_edges + num_queries == 0) break;

    FloydWarshallGraph graph(num_nodes);

    //Get edges
    for (int i = 0; i < num_edges; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      graph.add_edge(u, v, { w });
    }

    //Calculate shortest paths
    vector<vector<int> > dist = floydwarshall(graph);

    //Get queries
    for (int i = 0; i < num_queries; i++) {
      int u, v;
      cin >> u >> v;
      int d = dist[u][v];

      //Impossible
      if (d == numeric_limits<int>::max()) {
        cout << "Impossible" << endl;

        //Print result
      }
      else if (d == numeric_limits<int>::min()) {
        cout << "-Infinity" << endl;

      }
      else {
#ifdef PRINT_PATH
        vector<Node*> path = get_path(nodes[q]);
        for (int i = 0; i < path.size(); i++) {
          cout << path[i]->id << (i < path.size() - 1 ? ", " : "\n");
        }
#else
        cout << d << endl;
#endif
      }
    }
    cout << endl;
  }

  return 0;
}