// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <limits>
#include <vector>
#include <algorithm>

//Edge types
struct edge_weight {
  int weight;
};

struct edge_default {
};

//Node types
struct node_default {
};

//Forward declaration of node
template<typename E = edge_default, typename N = node_default>
class Node;

//Class representing an edge in a graph
template<typename E = edge_default, typename N = node_default>
class Edge {
public:
  Edge(Node<E, N>* left, Node<E, N>* right, E extra) : left(left), right(right), extra(extra) {}

  Node<E, N>* left;
  Node<E, N>* right;
  E extra;
};

//Class representing a node in a graph
template<typename E, typename N>
class Node {
public:
	Node(int id) : id(id) {}

  

  void add_edge(Edge<E, N>* edge) {
    edges.push_back(edge);
  }

	int id;
	std::vector<Edge<E,N>*> edges;
  N extra;
	
};

struct sort_edge_weight : public std::binary_function < Edge<edge_weight>*, Edge<edge_weight>*, bool > {
  bool operator()(const Edge<edge_weight> *x, const Edge<edge_weight> *y) const
  {
    return x->extra.weight > y->extra.weight;
  }
};

template<typename E, typename N>
struct sort_edge_lexi : public std::binary_function < Edge<E, N>*, Edge<E, N>*, bool > {
  bool operator()(const Edge<E, N> *x, const Edge<E, N> *y) const
  {
    if (x->left->id == y->left->id) {
      return x->right->id < y->right->id;
    }
    else {
      return x->left->id < y->left->id;
    }

  }
};

template<typename E = edge_default, typename N = node_default>
class Graph {
public:
  Graph(const size_t& graph_size) : nodes(graph_size) {
    //Create nodes
    for (size_t i = 0; i < graph_size; i++) {
      nodes[i] = new Node<E, N>(i);
    }
  }

  ~Graph() {
    for (auto n : nodes) {
      delete n;
    }
    for (auto e : edges) {
      delete e;
    }

  }

  size_t getSize() const {
    return nodes.size();
  }

  const std::vector<Node<E, N>*>& getNodes() const {
    return nodes;
  }

  const std::vector<Edge<E, N>*>& getEdges() const {
    return edges;
  }

  //Add an edge from this node to target with an optional weight
  void add_edge(const size_t& left, const size_t& right, E extra = E{}) {
    Edge<E, N>* edge = new Edge<E, N>(nodes[left], nodes[right], extra);
    edges.push_back(edge);
    nodes[left]->add_edge(edge);
    nodes[right]->add_edge(edge);
  }

  //Get node from graph
  Node<E, N>* operator[](const size_t& index) const {
    return nodes[index];
  }

private:
  std::vector<Node<E, N>*> nodes;
  std::vector<Edge<E, N>*> edges;
};