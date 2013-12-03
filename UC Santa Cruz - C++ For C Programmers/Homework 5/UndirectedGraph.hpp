// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// UndirectedGraph.hpp
// An undirected graph with zero-based indexed nodes.

#ifndef _HW5_UNDIRECTED_GRAPH_H_
#define _HW5_UNDIRECTED_GRAPH_H_

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T1, typename T2> // first type for nodes, second type for edges
class UndirectedGraph
{
public:
  // Constructor with specific default values for nodes and edges.
  // Creates a graph with no nodes or edges; nodes or edges added later will have the given defaults.
  // @param nodeDefault The default value for the nodes.
  // @param edgeDefault The default value for the edges.
  UndirectedGraph(const T1 nodeDefault, const T2 edgeDefault);

  // Gets the number of nodes in this graph.
  // @return The number of nodes in this graph.
  int getNumNodes();

  // Gets the number of edges in this graph.
  // @return The number of edges in this graph.
  int getNumEdges();

  // Test if there is an edge between two nodes.
  // @param node1 The first node; not checked, assumed to be valid.
  // @param node2 The second node; not checked, assumed to be valid.
  // @return True if an edge exists, otherwise false.
  bool isAdjacent(const int node1, const int node2);

  // Get all nodes connected to the given node.
  // @param node The node to check for any connections; assumed to be valid.
  // @param neighbors The reference vector of neighbors returned; any existing content will be cleared.
  void getNeighbors(const int node, vector<int> &neighbors);

  // Adds nodes to this graph.
  // @param n The number of nodes to add.
  void addNodes(const unsigned int n);
  // @param value The initial value to assign to the newly added nodes.
  void addNodes(const unsigned int n, const T1 value);

  // Adds an edge between the two nodes.
  // @param node1 The first node; not checked, assumed to be valid.
  // @param node2 The second node; not checked, assumed to be valid.
  void addEdge(const int node1, const int node2);
  // @param value The value of the newly added edge.
  void addEdge(const int node1, const int node2, const T2 value);

  // Delete the edge between the two nodes.
  // @param node1 The first node; not checked, assumed to be valid.
  // @param node2 The second node; not checked, assumed to be valid.
  void deleteEdge(const int node1, const int node2);

  // Returns the value associated with the node.
  // @param node The node whose value we want; not checked, assumed to be valid.
  // @return The value at that node.
  T1 getNodeValue(const int node);

  // Sets the value associated with the node.
  // @param node The node whose value we want to set; not checked, assumed to be valid.
  // @param value The value to set.
  void setNodeValue(const int node, const T1 value);

  // Returns the value associated with the edge between the two nodes.
  // @param node1 The first node; not checked, assumed to be valid.
  // @param node2 The second node; not checked, assumed to be valid.
  // @return The edge value.
  T2 getEdgeValue(const int node1, const int node2);

  // Sets the edge value between the two nodes.
  // @param node1 The first node; not checked, assumed to be valid.
  // @param node2 The second node; not checked, assumed to be valid.
  // @param dist The edge value to set.
  void setEdgeValue(const int node1, const int node2, const T2 value);

private:
  // The number of nodes in this undirected graph.
  int numNodes;

  // The number of edges in this undirected graph.
  int numEdges;

  // The graph, represented by an adjacency matrix.
  // Each element in the matrix has a boolean representing whether the nodes are
  // connected, and a value which represents the weight/distance between the nodes.
  vector<vector<pair<bool, T2>>> adjacencyMatrix;

  // The value of each node in this undirected graph.
  vector<T1> nodeValues;

  // The default value for a node.
  T1 nodeDefault;

  // The default value for an edge.
  T2 edgeDefault;

};

// Method definitions placed here to avoid clutter.

template <typename T1, typename T2>
UndirectedGraph<T1, T2>::UndirectedGraph(const T1 nodeDefault, const T2 edgeDefault)
  : numNodes(0),
    numEdges(0),
    nodeDefault(nodeDefault),
    edgeDefault(edgeDefault)
{

}

template <typename T1, typename T2>
inline int UndirectedGraph<T1, T2>::getNumNodes()
{
  return numNodes;
}

template <typename T1, typename T2>
inline int UndirectedGraph<T1, T2>::getNumEdges()
{
  return numEdges;
}

template <typename T1, typename T2>
inline bool UndirectedGraph<T1, T2>::isAdjacent(const int node1, const int node2)
{
  return adjacencyMatrix[node1][node2].first;
}

template <typename T1, typename T2>
void UndirectedGraph<T1, T2>::getNeighbors(const int node, vector<int> &neighbors)
{
  neighbors.clear();
  for (auto it = adjacencyMatrix[node].begin(); it != adjacencyMatrix[node].end(); ++it)
    if (it->first) neighbors.push_back(it - adjacencyMatrix[node].begin()); // nodes are connected
}

template <typename T1, typename T2>
inline void UndirectedGraph<T1, T2>::addNodes(const unsigned int n)
{
  addNodes(n, nodeDefault);
}

template <typename T1, typename T2>
void UndirectedGraph<T1, T2>::addNodes(const unsigned int n, const T1 value)
{
  numNodes += n;

  adjacencyMatrix.resize(numNodes);
  for (auto &vec : adjacencyMatrix)
    vec.resize(numNodes, pair<bool, T2>(false, edgeDefault));

  nodeValues.resize(numNodes, value);
}

template <typename T1, typename T2>
inline void UndirectedGraph<T1, T2>::addEdge(const int node1, const int node2)
{
  setEdgeValue(node1, node2, edgeDefault);
}

template <typename T1, typename T2>
inline void UndirectedGraph<T1, T2>::addEdge(const int node1, const int node2, const T2 value)
{
  setEdgeValue(node1, node2, value);
}

template <typename T1, typename T2>
inline void UndirectedGraph<T1, T2>::deleteEdge(const int node1, const int node2)
{
  adjacencyMatrix[node1][node2].first = false;
  adjacencyMatrix[node2][node1].first = false;
  --numEdges; // update the number of edges
}

template <typename T1, typename T2>
inline T1 UndirectedGraph<T1, T2>::getNodeValue(const int node)
{
  return nodeValues[node];
}

template <typename T1, typename T2>
inline void UndirectedGraph<T1, T2>::setNodeValue(const int node, const T1 value)
{
  nodeValues[node] = value;
}

template <typename T1, typename T2>
inline T2 UndirectedGraph<T1, T2>::getEdgeValue(const int node1, const int node2)
{
  return adjacencyMatrix[node1][node2].second;
}

template <typename T1, typename T2>
inline void UndirectedGraph<T1, T2>::setEdgeValue(const int node1, const int node2, const T2 value)
{
  if (!isAdjacent(node1, node2)) {
    ++numEdges;
    adjacencyMatrix[node1][node2].first = true;
    adjacencyMatrix[node2][node1].first = true;
  }

  adjacencyMatrix[node1][node2].second = value;
  adjacencyMatrix[node2][node1].second = value;
}

#endif // _HW5_UNDIRECTED_GRAPH_H_

