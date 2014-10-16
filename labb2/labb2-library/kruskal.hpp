// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <queue>

#include "unionfind.hpp"
#include "graph.hpp"

typedef Graph<edge_weight, node_default> KruskalGraph;
typedef Node<edge_weight, node_default> KruskalNode;
typedef Edge<edge_weight, node_default> KruskalEdge;

std::vector<KruskalEdge*> kruskal(KruskalGraph& graph) {
  //Init union find and edge priority queue
  UnionFind kruskal(graph.getSize());
  std::priority_queue<KruskalEdge*, vector<KruskalEdge*>, sort_edge_weight> edge_queue(graph.getEdges().begin(), graph.getEdges().end());
  std::vector<KruskalEdge*> result;

  //Look at all edges in weight order
  while (!edge_queue.empty()) {
    KruskalEdge* current = edge_queue.top();
    edge_queue.pop();

    //If both ends are in same component discard, otherwise save and unite components
    if (!kruskal.connected(current->left->id, current->right->id)) {
      kruskal.unite(current->left->id, current->right->id);
      result.push_back(current);
    }
  }

  if (result.size() == graph.getSize()-1) {
    std::sort(result.begin(), result.end(), sort_edge_lexi<edge_weight, node_default>());
    return result;
  }
  else {
    return std::vector<KruskalEdge*>();
  }
  
}