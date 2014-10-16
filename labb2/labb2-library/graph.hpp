// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <limits>
#include <vector>
#include <algorithm>

//Forward declaration of node
class Node;

//Class representing an edge in a graph
class Edge {
public:
	Edge(Node* left, Node* right, int weight = 0) : left(left), right(right), weight(weight) {}

  Node* left;
  Node* right;
	int weight;
};

//Class representing a node in a graph
class Node {
public:
	Node(int id) : id(id) {}

  //Get the path stored in this node
  std::vector<Node*> get_path() {
    std::vector<Node*> path;
    for (Node* v = this; v != NULL; v = v->previous)
      path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
  }

  void add_edge(Edge* edge) {
    edges.push_back(edge);
  }

	int id;
	std::vector<Edge*> edges;
	bool visited = false;
	Node* previous = NULL;
	int value = std::numeric_limits<int>::max();
};

struct sort_edge_weight : public std::binary_function < Edge*, Edge*, bool > {
  bool operator()(const Edge *x, const Edge *y) const
  {
    return x->weight > y->weight;
  }
};

struct sort_edge_lexi : public std::binary_function < Edge*, Edge*, bool > {
  bool operator()(const Edge *x, const Edge *y) const
  {
    if (x->left->id == y->left->id) {
      return x->right->id < y->right->id;
    }
    else {
      return x->left->id < y->left->id;
    }

  }
};

class Graph {
public:
  Graph(const size_t& graph_size) : nodes(graph_size) {
    //Create nodes
    for (size_t i = 0; i < graph_size; i++) {
      nodes[i] = new Node(i);
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

  const std::vector<Node*>& getNodes() const {
    return nodes;
  }

  const std::vector<Edge*>& getEdges() const {
    return edges;
  }

  //Add an edge from this node to target with an optional weight
  void add_edge(const size_t& left, const size_t& right, int weight = 0) {
    Edge* edge = new Edge(nodes[left], nodes[right], weight);
    edges.push_back(edge);
    nodes[left]->add_edge(edge);
    nodes[right]->add_edge(edge);
  }

  //Get node from graph
  Node* operator[](const size_t& index) const {
    return nodes[index];
  }

private:
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;
};