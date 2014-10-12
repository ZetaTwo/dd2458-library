#include <climits>
#include <string>
#include <vector>

class Node;

class Edge {
public:
	Edge(Node& target, int weight=0) : target(&target), weight(weight) {}

	Node* target;
	int weight;
};

class Node {
public:
	Node(std::string name) : name(name) {}
	Node(int id) : id(id) {}
	void add_edge(Node& target, int weight=0) {
		edges.push_back( new Edge(target, weight) );
	}

	std::string name;
	int id;
	std::vector<Edge*> edges;
	bool visited = false;
	Node* previous = NULL;
	int value = INT_MAX;
};

