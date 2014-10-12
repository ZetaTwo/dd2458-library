// kth d2458 popuph14
// author: magolsso@kth.se

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include "graph.hpp"
using namespace std;

// #define PRINT_PATH

// ------------------------------------------------------------------------- //

void dijkstra(Node* start) {
	queue<Node*> q;
	start->value = 0;
	q.push(start);

	while (!q.empty()) {
		Node* current = q.front();
		q.pop();

		for (Edge* e : current->edges) {
			Node* t = e->target;
			int dist = current->value + e->weight;
			if (dist < t->value) {
				t->value = dist;
				t->previous = current;
				q.push(t);
			}
		}
	}
}

// ------------------------------------------------------------------------- //

vector<Node*> get_path(Node* target) {
	vector<Node*> path;
	for (Node* v = target; v != NULL; v = v->previous)
		path.push_back(v);
	reverse(path.begin(), path.end());
	return path;
}

// ------------------------------------------------------------------------- //

int main() {

	while (true) {
		int num_nodes, num_edges, num_queries, start_node;
		scanf("%d %d %d %d\n", &num_nodes, &num_edges, &num_queries, &start_node);
		if (num_nodes+num_edges+num_queries+start_node == 0) break;

		vector<Node*> nodes(num_nodes);
		for (int i = 0; i < num_nodes; i++) {
			nodes[i] = new Node(i);
		}

		for (int i = 0; i < num_edges; i++) {
			int fr, to, w;
			scanf("%d %d %d", &fr, &to, &w);
			nodes[fr]->add_edge(*nodes[to], w);
		}

		dijkstra(nodes[start_node]);

		for (int i = 0; i < num_queries; i++) {
			int q;
			scanf("%d", &q);
			int dist = nodes[q]->value;
			if (dist == INT_MAX) {
				printf("Impossible\n");
			} else {
#ifdef PRINT_PATH
				vector<Node*> path = get_path(nodes[q]);
				for (int i = 0; i < path.size(); i++) {
					cout << path[i]->id << (i < path.size()-1?", ":"\n");
				}
#else
				printf("%d\n", dist);
#endif
			}
		}
		printf("\n");
	}
}