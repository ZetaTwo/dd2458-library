// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <iostream>
#include <vector>
using namespace std;

#include "dijkstra.hpp"

// Do we want to show the calculated path?
// #define PRINT_PATH

// SDL compatibility
#ifdef _WIN32
#define scanf scanf_s
#endif

int main() {
  //For each test case
	while (true) {

    //Get inputs
		int num_nodes, num_edges, num_queries, start_node;
    cin >> num_nodes >> num_edges >> num_queries >> start_node;
		if (num_nodes+num_edges+num_queries+start_node == 0) break;

    DijkstraGraph graph(num_nodes);

    //Get edges
		for (int i = 0; i < num_edges; i++) {
			int fr, to, w;
      cin >> fr >> to >> w;
      graph.add_edge(fr, to, { w });
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
			} else {
#ifdef PRINT_PATH
				vector<Node*> path = get_path(nodes[q]);
				for (int i = 0; i < path.size(); i++) {
					cout << path[i]->id << (i < path.size()-1?", ":"\n");
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