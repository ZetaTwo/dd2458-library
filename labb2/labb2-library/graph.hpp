// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <limits>
#include <vector>
#include <algorithm>

//Default edge and node types
struct edge_default {};
struct node_default {};

//Forward declaration of node
template<typename E = edge_default, typename N = node_default>
class Node;

//Other edge and node types
struct edge_weight {
  int weight;
};

template<typename E>
struct node_val_prev {
  int value = std::numeric_limits<int>::max();
  Node<E, node_val_prev>* previous = NULL;
};

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
  typedef E edge_type;
  typedef N node_type;
};

//Help function to get path
//Get the path stored in this node
template<typename T>
std::vector<T*> get_path(T* end) {
  std::vector<T*> path;
  for (T* v = end; v != NULL; v = v->extra.previous)
    path.push_back(v);
  std::reverse(path.begin(), path.end());
  return path;
}

//Functor for sorting edges according to weight
struct sort_edge_weight : public std::binary_function < Edge<edge_weight>*, Edge<edge_weight>*, bool > {
  bool operator()(const Edge<edge_weight> *x, const Edge<edge_weight> *y) const
  {
    return x->extra.weight > y->extra.weight;
  }
};

//Functor for sorting edges according to lexicographical order ( (0 1) < (0 2) < (1 2) )
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

//Class representing a graph of fixed size
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