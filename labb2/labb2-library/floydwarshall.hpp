// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <vector>
#include <limits>

#include "graph.hpp"

//Typedefs for edges, nodes and graph to shorten code
typedef Graph<edge_weight> FloydWarshallGraph;
typedef Node<edge_weight> FloydWarshallNode;
typedef Edge<edge_weight> FloydWarshallEdge;

std::vector<std::vector<int> > floydwarshall(const FloydWarshallGraph& graph) {
  const size_t V = graph.getSize();
  
  //Init DP table
  std::vector<std::vector<int> > dist(V, std::vector<int>(V, std::numeric_limits<int>::max()));
  for (size_t i = 0; i < V; i++)
  {
    dist[i][i] = 0;
  }
  for (auto e : graph.getEdges()) {
    if (dist[e->left->id][e->right->id] > e->extra.weight) {
      dist[e->left->id][e->right->id] = e->extra.weight;
    }
  }

  //Perform DP (twice to properly detect all negative cycles)
  for (size_t twice = 0; twice < 2; twice++) {
    for (size_t k = 0; k < V; k++)
    {
      for (size_t i = 0; i < V; i++)
      {
        for (size_t j = 0; j < V; j++)
        {
          //Feasible parts?
          if (dist[i][k] == std::numeric_limits<int>::max() ||
            dist[k][j] == std::numeric_limits<int>::max()) {
            continue;
          }

          //Negative cycles?
          if (dist[i][k] == std::numeric_limits<int>::min() ||
            dist[k][j] == std::numeric_limits<int>::min()) {
            dist[i][j] = std::numeric_limits<int>::min();

          //Standard case
          }
          else if (dist[i][j] > dist[i][k] + dist[k][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }

          //Detect negative self-cycle
          if (i == j && dist[i][j] < 0) {
            dist[i][j] = std::numeric_limits<int>::min();
          }
        }
      }
    }
  }

  return dist;
}