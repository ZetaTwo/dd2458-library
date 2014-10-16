// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <queue>

#include "unionfind.hpp"
#include "graph.hpp"

std::vector<Edge*> kruskal(Graph& graph) {
  //Init union find and edge priority queue
  UnionFind kruskal(graph.getSize());
  std::priority_queue<Edge*, vector<Edge*>, sort_edge_weight> edge_queue(graph.getEdges().begin(), graph.getEdges().end());
  std::vector<Edge*> result;

  //Look at all edges in weight order
  while (!edge_queue.empty()) {
    Edge* current = edge_queue.top();
    edge_queue.pop();

    //If both ends are in same component discard, otherwise save and unite components
    if (!kruskal.connected(current->left->id, current->right->id)) {
      kruskal.unite(current->left->id, current->right->id);
      result.push_back(current);
    }
  }

  if (result.size() == graph.getSize()-1) {
    std::sort(result.begin(), result.end(), sort_edge_lexi());
    return result;
  }
  else {
    return std::vector<Edge*>();
  }
  
}