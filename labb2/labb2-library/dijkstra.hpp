// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <queue>
#include <limits>

#include "graph.hpp"

//Edge properties in timetable Dijkstra
struct edge_dijsktra_timetable {
  int start;
  int interval;
  int weight;
};

//Typedefs for edges, nodes and graph to shorten code
typedef Graph<edge_weight, node_val_prev<edge_weight> > DijkstraGraph;
typedef Node<edge_weight, node_val_prev<edge_weight> > DijkstraNode;
typedef Edge<edge_weight, node_val_prev<edge_weight> > DijkstraEdge;

typedef Graph<edge_dijsktra_timetable, node_val_prev<edge_dijsktra_timetable> > DijkstraTimeTableGraph;
typedef Node<edge_dijsktra_timetable, node_val_prev<edge_dijsktra_timetable> > DijkstraTimeTableNode;
typedef Edge<edge_dijsktra_timetable, node_val_prev<edge_dijsktra_timetable> > DijkstraTimeTableEdge;

//Sorting function for sorting nodes according to value
template<typename N>
struct sort_node_value : public std::binary_function < Node<typename N::edge_type, typename N::node_type>*, Node<typename N::edge_type, typename N::node_type>*, bool > {
  int operator() (const Node<typename N::edge_type, typename N::node_type>* n1, const Node<typename N::edge_type, typename N::node_type>* n2) {
    return n1->extra.value > n2->extra.value;
  }
};

//Calculate the distance from node to next through edge
int dijkstra_dist(const DijkstraEdge& edge, const DijkstraNode&node) {
  return node.extra.value + edge.extra.weight;
}

//Calculate the distance from node to next through edge with timetable constraints
int dijkstra_dist(const DijkstraTimeTableEdge& edge, const DijkstraTimeTableNode&node) {
  if (edge.extra.interval == 0) {
    if (node.extra.value > edge.extra.start) {
      return std::numeric_limits<int>::max();
    }
    else {
      return edge.extra.start + edge.extra.weight;
    }
  }
  else {
    if (node.extra.value > edge.extra.start) {
      int pp = 1 + (((node.extra.value - edge.extra.start) - 1) / edge.extra.interval);
      return edge.extra.start + pp * edge.extra.interval + edge.extra.weight;
    }
    else {
      return edge.extra.start + edge.extra.weight;
    }
  }
}

//Perform dijkstra's algorithm from start node to all other nodes
//After returning, every node in the graph will contain the length of the shortest path from start to that node.
template<typename N>
void dijkstra(N* start) {
  //Iniate the queue and starting length
  std::priority_queue<N*, std::vector<N*>, sort_node_value<N> > q;
  start->extra.value = 0;
  q.push(start);

  //For each remaining node
  while (!q.empty()) {
    N* current = q.top();
    q.pop();

    //Search all adjacent nodes
    for (auto e : current->edges) {
      N* t = e->right;

      //Calculate distance
      int dist = dijkstra_dist(*e, *current);
      if (dist == std::numeric_limits<int>::max()) {
        continue;
      }

      //If this value is better, update and queue
      if (dist < t->extra.value) {
        t->extra.value = dist;
        t->extra.previous = current;
        q.push(t);
      }
    }
  }
}
