// UC Santa Cruz C++ For C Programmers
// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// TH Hee
// UndirectedGraph.cpp

#include "UndirectedGraph.hpp"

UndirectedGraph::UndirectedGraph(int numNodes, double density, pair<double, double> distRange)
{
  this->numNodes = numNodes;
  this->numEdges = 0;

  adjacencyMatrix.resize(numNodes);
  for (auto it = adjacencyMatrix.begin(); it != adjacencyMatrix.end(); ++it)
    it->resize(numNodes, 0.0);

  nodeValues.resize(numNodes, numeric_limits<double>::max());

  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on the current time
  default_random_engine generator(seed);

  // initialize uniform distributions for the graph density and edge distance calculations
  uniform_real_distribution<double> densityDistribution(0.0, 1.0);
  uniform_real_distribution<double> edgeDistDistribution(distRange.first, distRange.second);

  // iterate all pairs of nodes, checking pairs only once and omitting nodes where i == j
  for (int i = 0; i < numNodes - 1; ++i) {
    for (int j = i + 1; j < numNodes; ++j) {
      if (densityDistribution(generator) < density) // probability calculation is less than the density
        addEdge(i, j, edgeDistDistribution(generator)); // add an edge between the nodes with a distance given by the distribution
    }
  }
}

UndirectedGraph::UndirectedGraph(const char* filename)
{
  ifstream infile(filename);

  infile >> numNodes;
  numEdges = 0;

  adjacencyMatrix.resize(numNodes);
  for (auto it = adjacencyMatrix.begin(); it != adjacencyMatrix.end(); ++it)
    it->resize(numNodes, 0.0);

  nodeValues.resize(numNodes, numeric_limits<double>::max());

  // read integer triples and process each set
  int node1, node2, cost;
  while (infile >> node1 >> node2 >> cost)
    addEdge(node1, node2, static_cast<double>(cost));
}

void UndirectedGraph::getNeighbors(int node, vector<int> &neighbors)
{
  neighbors.clear();
  for (auto it = adjacencyMatrix[node].begin(); it != adjacencyMatrix[node].end(); ++it) {
    if (*it != 0.0)
      neighbors.push_back(it - adjacencyMatrix[node].begin());
  }
}

