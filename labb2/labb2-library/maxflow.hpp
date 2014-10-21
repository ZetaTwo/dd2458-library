// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <cassert>
#include <cmath>
#include <vector>

#include "graph.hpp"

//Edge and node types
struct edge_flow {
  int capacity;
  int flow;
};
struct node_excess {
  int excess = 0;
  int height = 0;
};

//Typedefs for edges, nodes and graph to shorten code
typedef Graph<edge_flow, node_excess> MaxFlowGraph;
typedef Node<edge_flow, node_excess> MaxFlowNode;
typedef Edge<edge_flow, node_excess> MaxFlowEdge;

int excess(MaxFlowNode* node, const size_t& start) {
  if (node->id == start) {
    return std::numeric_limits<int>::max();
  }
  else {
    return node->extra.excess;
  }
}

//TODO: Push back excess?
bool push(MaxFlowEdge* edge, std::vector<std::vector<int> >& flow, const size_t& start) {
  //Assertions
  if (!(excess(edge->left, start) > 0 && edge->left->extra.height == edge->right->extra.height + 1)) { return false; }

  //Calculate push
  int delta = std::min(excess(edge->left, start), edge->extra.capacity - flow[edge->left->id][edge->right->id]);
  if (delta == 0) {
    return false;
  }

  flow[edge->left->id][edge->right->id] += delta;
  flow[edge->right->id][edge->left->id] -= delta;

  //Subtract/add unless source which is inf
  if (edge->left->id != start) {
    edge->left->extra.excess -= delta;
  } 
  if (edge->right->id != start) {
    edge->right->extra.excess += delta;
  }

  return true;
}

bool relabel(MaxFlowNode* node, std::vector<std::vector<int> >& flow, const size_t& start, const size_t& end) {
  //Assertions
  if (node->id == start || node->id == end) { return false; }
  if (!(excess(node, start) > 0)) { return false; };
  for (auto e : node->edges) {
    if (e->left == node && flow[e->left->id][e->right->id] < e->extra.capacity) {
      if (!(e->left->extra.height <= e->right->extra.height)) {
        return false;
      }
    }
  }

  //Calculate new label
  int min_height = std::numeric_limits<int>::max();
  for (auto e : node->edges)
  {
    if (e->left == node && flow[e->left->id][e->right->id] < e->extra.capacity && e->right->extra.height < min_height) {
      min_height = e->right->extra.height;
    }
  }
  if (min_height == std::numeric_limits<int>::max()) {
    return false;
  }

  node->extra.height = min_height + 1;

  return true;
}

int maxflow(MaxFlowGraph& graph, const size_t& source, const size_t& sink, std::vector<MaxFlowEdge*>& flow_graph) {
  //flow table
  std::vector<std::vector<int> > flow(graph.getSize(), std::vector<int>(graph.getSize(), 0));

  //create a preflow f that saturates all out-edges of s
  for (auto& e : graph.getNodes()[source]->edges)
  {
    if (e->left == graph.getNodes()[source]) {
      flow[e->left->id][e->right->id] += e->extra.capacity;
      e->right->extra.excess += e->extra.capacity;
    }
  }
  MaxFlowNode* source_node = graph.getNodes()[source];
  for (auto& e : source_node->edges)
  {
    push(e, flow, source);
  }

  //let h[u] = 0 foreach v in graph
  for (auto& v : graph.getNodes())
  {
    v->extra.height = 0;
  }

  graph.getNodes()[source]->extra.height = graph.getSize();
  graph.getNodes()[sink]->extra.height = 0;
  
  bool did_work = false;
  do {
    did_work = false;
    for (auto& v : graph.getNodes())
    {
      if (relabel(v, flow, source, sink)) {
        did_work = true;
      }
    }
    for (auto& e : graph.getEdges())
    {
      if (push(e, flow, source)) {
        did_work = true;
      }
    }

  } while (did_work);

  //Create resulting graph with flows
  int sum = 0;
  for (auto& e : graph.getEdges())
  {
    e->extra.flow = flow[e->left->id][e->right->id];
    if (e->right->id == sink) {
      sum += e->extra.flow;
    }
    if (e->extra.flow > 0) {
      flow_graph.push_back(e);
    }
  }

  return sum;
}