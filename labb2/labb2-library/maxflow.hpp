// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se
#pragma once

#include <cassert>
#include <cmath>
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <algorithm>

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

bool bfs(const std::vector<std::vector<int> >& rGraph, int s, int t, std::vector<int>& parent, const vector<set<int>>&edges)
{
  const size_t& V = rGraph.size();
  // Create a visited array and mark all vertices as not visited
  std::vector<bool> visited(V, false);

  // Create a queue, enqueue source vertex and mark source vertex
  // as visited
  std::queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  // Standard BFS Loop
  while (!q.empty())
  {
    int u = q.front();
    q.pop();

    //for (int v = 0; v < V; v++)
    for (auto v : edges[u])
    {
      if (visited[v] == false && rGraph[u][v] > 0)
      {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  // If we reached sink in BFS starting from source, then return
  // true, else false
  return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(const std::vector<std::vector<int> >& graph, int s, int t, std::vector<std::vector<int> >& flowGraph, const vector<set<int>>&edges)
{
  const size_t& V = graph.size();
  int u, v;

  // Create a residual graph and fill the residual graph with
  // given capacities in the original graph as residual capacities
  // in residual graph
  std::vector<std::vector<int> > rGraph(V, std::vector<int>(V)); // Residual graph where rGraph[i][j] indicates 
  // residual capacity of edge from i to j (if there
  // is an edge. If rGraph[i][j] is 0, then there is not)  
  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++)
      rGraph[u][v] = graph[u][v];

  std::vector<int> parent(V);  // This array is filled by BFS and to store path

  int max_flow = 0;  // There is no flow initially

  // Augment the flow while there is path from source to sink
  while (bfs(rGraph, s, t, parent, edges))
  {
    // Find minimum residual capacity of the edges along the
    // path filled by BFS. Or we can say find the maximum flow
    // through the path found.
    int path_flow = std::numeric_limits<int>::max();
    for (v = t; v != s; v = parent[v])
    {
      u = parent[v];
      path_flow = std::min(path_flow, rGraph[u][v]);
    }

    // update residual capacities of the edges and reverse edges
    // along the path
    for (v = t; v != s; v = parent[v])
    {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }

    // Add path flow to overall flow
    max_flow += path_flow;
  }

  //Construct flow
  
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      flowGraph[i][j] = std::max(graph[i][j] - rGraph[i][j], 0);
    }
  }

  // Return the overall flow
  return max_flow;
}