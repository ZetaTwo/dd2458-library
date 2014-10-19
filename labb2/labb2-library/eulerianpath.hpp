// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
//
// Based on: http://en.wikipedia.org/wiki/Eulerian_path#Hierholzer.27s_algorithm
//      and: http://stones333.blogspot.se/2013/11/find-eulerian-path-in-directed-graph.html
#pragma once

#include <list>
#include <stack>

#include "graph.hpp"

//Edge and node types
struct edge_visited {
  bool used = false;
};
struct node_degrees {
  int indeg = 0;
  int outdeg = 0;
  bool visited = false;
};

//Typedefs for edges, nodes and graph to shorten code
typedef Graph<edge_visited, node_degrees > EulerGraph;
typedef Node<edge_visited, node_degrees > EulerNode;
typedef Edge<edge_visited, node_degrees > EulerEdge;

//Get an unvisited edge from node and marks it as visited
EulerEdge* getUnvisited(const EulerNode* node) {
  for (auto e : node->edges) {
    if (e->left == node && !e->extra.used) {
      e->extra.used = true;
      return e;
    }
  }
  return NULL;
}

std::vector<size_t> eulerianpath(EulerGraph& graph) {
  int out_odd = -1;
  int in_odd = -1;

  //Count in & out degrees for all nodes
  for (auto n : graph.getNodes())
  {
    for (auto e : n->edges)
    {
      if (e->left == n) {
        n->extra.outdeg++;
      }
      if (e->right == n) {
        n->extra.indeg++;
      }
    }

    //Detect if possible
    //Either (all nodes with indeg = outdeg) or (exactly one node with outdeg-indeg = 1 and exactly one with outdeg-indeg = -1)
    if (abs(n->extra.indeg - n->extra.outdeg) > 1) {
      return std::vector<size_t>();
    } else if (n->extra.indeg - n->extra.outdeg == 1) {
      if (in_odd < 0) {
        in_odd = n->id;
      }
      else {
        return std::vector<size_t>();
      }
    }
    else if (n->extra.outdeg - n->extra.indeg == 1) {
      if (out_odd < 0) {
        out_odd = n->id;
      }
      else {
        return std::vector<size_t>();
      }
    }
  }

  //Choose start node
  EulerNode* start = NULL;
  if (out_odd >= 0) {
    start = graph.getNodes()[out_odd];
  }
  else {
    for (auto n : graph.getNodes()) {
      if (n->edges.size() > 0) {
        start = n;
        break;
      }
    }
  }
  if (start == NULL) {
    return std::vector<size_t>();
  }
  
  //Perform Hierholzer from start node
  std::stack<EulerEdge*> forward;
  std::stack<EulerEdge*> backtrack;
  EulerEdge* current = getUnvisited(start);
  //Initial cycles
  while (current != NULL) {
    current->extra.used = true;
    forward.push(current);
    current = getUnvisited(current->right);
  }
  //Augment cycles
  while ((!forward.empty())) {
    current = forward.top();
    forward.pop();
    backtrack.push(current);
    current = getUnvisited(current->left);
    while (current != NULL) {
      current->extra.used = true;
      forward.push(current);
      current = getUnvisited(current->right);
    }
  }
  
  //Did we really use all edges (connected graph?)
  for (auto e : graph.getEdges())
  {
    if (!e->extra.used) {
      return std::vector<size_t>();
    }
  }

  //Convert stack to path, preprend start and return result
  std::vector<size_t> result;
  result.push_back(backtrack.top()->left->id);
  while (!backtrack.empty()) {
    EulerEdge* edge = backtrack.top();
    backtrack.pop();
    result.push_back(edge->right->id);
  }
  return result;
}