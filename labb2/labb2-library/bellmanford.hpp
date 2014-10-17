// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <queue>
#include <limits>

#include "graph.hpp"

//Typedefs for edges, nodes and graph to shorten code
typedef Graph<edge_weight, node_val_prev<edge_weight> > BellmanFordGraph;
typedef Node<edge_weight, node_val_prev<edge_weight> > BellmanFordNode;
typedef Edge<edge_weight, node_val_prev<edge_weight> > BellmanFordEdge;

void bellmanford(BellmanFordGraph& graph, const size_t& start) {
  //Step 1: Init
  graph[start]->extra.value = 0;

  //Step 2: Relax nodes
  for (size_t i = 1; i < graph.getSize(); i++)
  {
    for (auto e : graph.getEdges())
    {
      if (e->left->extra.value != std::numeric_limits<int>::max() && e->left->extra.value + e->extra.weight < e->right->extra.value) {
        e->right->extra.value = e->left->extra.value + e->extra.weight;
        e->right->extra.previous = e->left;
      }
    }
  }

  //Step 3: Detect negative cycles
  for (size_t i = 1; i < graph.getSize(); i++)
  {
    for (auto e : graph.getEdges())
    {
      if (e->left->extra.value == std::numeric_limits<int>::min()) {
        e->right->extra.value = std::numeric_limits<int>::min();
      }
      else if (e->left->extra.value != std::numeric_limits<int>::max() && e->left->extra.value + e->extra.weight < e->right->extra.value) {
        e->right->extra.value = std::numeric_limits<int>::min();
      }
    }
  }
}