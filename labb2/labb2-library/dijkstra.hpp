// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <queue>

#include "graph.hpp"

//Perform dijkstra's algorithm from start node to all other nodes
//After returning, every node in the graph will contain the length of the shortest path from start to that node.
struct node_dijsktra {
  int value = std::numeric_limits<int>::max();
  Node<edge_weight, node_dijsktra>* previous = NULL;
};

typedef Graph<edge_weight, node_dijsktra> DijkstraGraph;
typedef Node<edge_weight, node_dijsktra> DijkstraNode;
typedef Edge<edge_weight, node_dijsktra> DijkstraEdge;

//Get the path stored in this node
std::vector<DijkstraNode*> get_dijkstra_path(DijkstraNode* end) {
  std::vector<DijkstraNode*> path;
  for (DijkstraNode* v = end; v != NULL; v = v->extra.previous)
    path.push_back(v);
  std::reverse(path.begin(), path.end());
  return path;
}

template<typename E>
struct sort_node_value : public std::binary_function < Node<E, node_dijsktra>*, Node<E, node_dijsktra>*, bool > {
  int operator() (const Node<E, node_dijsktra>* n1, const Node<E, node_dijsktra>* n2) {
    return n1->extra.value > n2->extra.value;
  }
};

void dijkstra(DijkstraNode* start) {
  //Iniate the queue and starting length
  std::priority_queue<DijkstraNode*, std::vector<DijkstraNode*>, sort_node_value<edge_weight> > q;
  start->extra.value = 0;
  q.push(start);

  //For each remaining node
  while (!q.empty()) {
    DijkstraNode* current = q.top();
    q.pop();

    //Search all adjacent nodes
    for (DijkstraEdge* e : current->edges) {
      DijkstraNode* t = e->right;
      int dist = current->extra.value + e->extra.weight;

      //If this value is better, update and queue
      if (dist < t->extra.value) {
        t->extra.value = dist;
        t->extra.previous = current;
        q.push(t);
      }
    }
  }
}
