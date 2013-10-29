// UC Santa Cruz C++ For C Programmers
// Homework 2: Implement Dijkstra's Algorithm
// TH Hee
// UndirectedGraph.hpp

#ifndef _HW2_UNDIRECTED_GRAPH_H_
#define _HW2_UNDIRECTED_GRAPH_H_

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <limits>
#include <chrono>
#include <random>

using namespace std;

class UndirectedGraph
{
public:
  // Constructor.
  // @param numNodes The number of nodes in this graph.
  // @param density The edge density of this graph, from 0.0 to 1.0.
  // @param distRange The edge distance range (min and max values).
  UndirectedGraph(int numNodes, double density, pair<double, double> distRange);

  // Returns the number of nodes in this graph.
  // @return The number of nodes in this graph.
  inline int getNumNodes();

  // Returns the number of edges in this graph.
  // @return The number of edges in this graph.
  inline int getNumEdges();

  // Test if there is an edge between two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @return True if an edge exists, otherwise false.
  inline bool isAdjacent(int node1, int node2);

  // Get all nodes connected to the given node.
  // @param node The node to check for any connections.
  // @return The vector of connected nodes.
  vector<int> getNeighbors(int node);

  // Adds an edge between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @param dist The edge distance (optional).
  inline void addEdge(int node1, int node2, double dist = 0.0);

  // Delete the edge between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  inline void deleteEdge(int node1, int node2);

  // Returns the value associated with the node.
  // @param node The node whose value we want.
  // @return The value at that node.
  inline double getNodeValue(int node);

  // Sets the value associated with the node.
  // @param node The node whose value we want to set.
  // @param value The value to set.
  inline void setNodeValue(int node, double value);

  // Returns the value associated with the edge between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @return The edge value.
  inline double getEdgeValue(int node1, int node2);

  // Sets the edge value between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @param dist The edge value to set.
  inline void setEdgeValue(int node1, int node2, double value);

private:
  // The number of nodes in this undirected graph.
  int numNodes;

  // The number of edges in this undirected graph.
  int numEdges;

  // The adjacency list representing this undirected graph.
  // Each vector element is a key-value pair, where the key represents the
  // connected node, and the the value represents the edge distance.
  vector<unordered_map<int, double>> nodeList;

  // The value of each node in this undirected graph.
  vector<double> nodeValues;

};

#endif // _HW2_UNDIRECTED_GRAPH_H_

