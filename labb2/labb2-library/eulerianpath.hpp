// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
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

std::vector<size_t> eulerianpath(EulerGraph& graph) {
  int out_odd = -1;
  int in_odd = -1;

  for (auto n : graph.getNodes())
  {
    //Count degrees
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

  //Is it possible?
  std::list<size_t> path;
  if (in_odd >= 0) {
    //path.push_back(in_odd);
  } 
  if (out_odd >= 0) {
    path.push_front(out_odd);
  }
  else {
    path.push_front(0);
  }
  
 
  std::list<size_t>::iterator last_possible = path.begin();
  const std::vector<EulerNode*>& nodes = graph.getNodes();
  nodes[path.front()]->extra.visited = true;
  while (last_possible != path.end()) {
    size_t current = *last_possible;
    std::list<size_t>::iterator insert_pos = last_possible;
    insert_pos++;

    bool first = true;
    while (first || current != *last_possible) {
      first = false;

      bool found = false;
      for (auto e : nodes[current]->edges) {
        if (e->left->id == current && !e->extra.used) {
          e->extra.used = true;
          current =  e->right->id;
          nodes[current]->extra.visited = true;
          found = true;
          break;
        }
      }

      if (!found) {
        break;
      }

      path.insert(insert_pos, current);
    }

    last_possible++;
  }

  for (auto e : graph.getEdges())
  {
    if (!e->extra.used) {
      return std::vector<size_t>();
    }
  }
  for (auto n : graph.getNodes())
  {
    if (!n->extra.visited) {
      return std::vector<size_t>();
    }
  }

  return std::vector<size_t>(path.begin(), path.end());
}