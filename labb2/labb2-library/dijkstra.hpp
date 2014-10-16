// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <queue>

#include "graph.hpp"

//Perform dijkstra's algorithm from start node to all other nodes
//After returning, every node in the graph will contain the length of the shortest path from start to that node.
void dijkstra(Node* start) {
  //Iniate the queue and starting length
  std::queue<Node*> q;
  start->value = 0;
  q.push(start);

  //For each remaining node
  while (!q.empty()) {
    Node* current = q.front();
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
