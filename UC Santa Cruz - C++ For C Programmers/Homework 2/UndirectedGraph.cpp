// UC Santa Cruz C++ For C Programmers
// Homework 2: Implement Dijkstra's Algorithm
// TH Hee
// UndirectedGraph.cpp

#include "UndirectedGraph.hpp"

UndirectedGraph::UndirectedGraph(int numNodes, double density, pair<double, double> distRange)
{
  this->numNodes = numNodes; // initialize the number of nodes
  this->numEdges = 0; // initialize the number of edges

  for (int i = 0; i < numNodes; i++) { // iterate the number of nodes
    nodeList.push_back(unordered_map<int, double>()); // initialize the adjacency list
    nodeValues.push_back(numeric_limits<double>::max()); // initialize the node values
  }

  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on the current time
  default_random_engine generator(seed); // seed the random number engine

  // initialize uniform distributions for the graph density and edge distance calculations
  uniform_real_distribution<double> densityDistribution(0.0, 1.0);
  uniform_real_distribution<double> edgeDistDistribution(distRange.first, distRange.second);

  // iterate all pairs of nodes, checking pairs only once and omitting nodes where i == j
  for (int i = 0; i < numNodes - 1; i++) {
    for (int j = i + 1; j < numNodes; j++) {
      if (densityDistribution(generator) < density) { // probability calculation is less than the density
        addEdge(i, j, edgeDistDistribution(generator)); // add an edge between the nodes with a distance given by the distribution
      }
    }
  }
}

vector<int> UndirectedGraph::getNeighbors(int node)
{
  vector<int> connectedNodes; // initialize the vector of connected nodes

  for (auto it = nodeList.at(node).begin(); it != nodeList.at(node).end(); ++it) // iterate the map
    connectedNodes.push_back(it->first); // store the keys (the connected nodes)

  return connectedNodes;
}

