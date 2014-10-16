// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <queue>

#include "graph.hpp"

// Comparator function which makes priority_queue smallest first
struct comp {
    int operator() (const Node* n1,const Node* n2) {
        return n1->value > n2->value;
    }
};

//Perform dijkstra's algorithm from start node to all other nodes
//After returning, every node in the graph will contain the length of the shortest path from start to that node.
void dijkstra(Node* start) {
  //Iniate the queue and starting length
  std::priority_queue<Node*, std::vector<Node*>, comp> q;
  start->value = 0;
  q.push(start);

  //For each remaining node
  while (!q.empty()) {
    Node* current = q.top();
    q.pop();

    //Search all adjacent nodes
    for (Edge* e : current->edges) {
      Node* t = e->right;
      int dist = current->value + e->weight;

      //If this value is better, update and queue
      if (dist < t->value) {
        t->value = dist;
        t->previous = current;
        q.push(t);
      }
    }
  }
}
