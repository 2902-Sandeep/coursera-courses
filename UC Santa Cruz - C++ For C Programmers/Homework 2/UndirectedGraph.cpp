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
  uniform_real_distribution<double> edgeDistDistribution(1.0, 10.0);

  // iterate all pairs of nodes, checking pairs only once and omitting nodes where i == j
  for (int i = 0; i < numNodes - 1; i++) {
    for (int j = i + 1; j < numNodes; j++) {
      double densityValue = densityDistribution(generator);
      cout << i << " " << j << " " << densityValue;
      if (densityValue < density) {
//      if (densityDistribution(generator) < density) { // probability calculation is less than the density
//        addEdge(i, j, edgeDistDistribution(generator)); // add an edge between the nodes with a distance given by the distribution
        numEdges++; // increment the number of edges
        double edgeLength = edgeDistDistribution(generator);
        addEdge(i, j, edgeLength);
        cout << " edge length: " << edgeLength;
      }
      cout << endl;
    }
  }
}

inline int UndirectedGraph::getNumNodes()
{
  return numNodes;
}

inline int UndirectedGraph::getNumEdges()
{
  return numEdges;
}

inline bool UndirectedGraph::isAdjacent(int node1, int node2)
{
  // go to the index specified by node1 and search for the key specified by node2
  return nodeList.at(node1).count(node2) > 0;
}

vector<int> UndirectedGraph::getNeighbors(int node)
{
  vector<int> connectedNodes; // initialize the vector of connected nodes

  for (auto it = nodeList.at(node).begin(); it != nodeList.at(node).end(); ++it) // iterate the map
    connectedNodes.push_back(it->first); // store the keys (the connected nodes)

  return connectedNodes;
}

inline void UndirectedGraph::addEdge(int node1, int node2, double dist /*=0.0*/)
{
  setEdgeValue(node1, node2, dist);
}

inline void UndirectedGraph::deleteEdge(int node1, int node2)
{
  nodeList.at(node1).erase(node2);
  nodeList.at(node2).erase(node1);
}

inline double UndirectedGraph::getNodeValue(int node)
{
  return nodeValues.at(node);
}

inline void UndirectedGraph::setNodeValue(int node, double value)
{
  nodeValues.at(node) = value;
}

inline double UndirectedGraph::getEdgeValue(int node1, int node2)
{
  return nodeList.at(node1).at(node2);
}

inline void UndirectedGraph::setEdgeValue(int node1, int node2, double value)
{
  nodeList.at(node1)[node2] = value;
  nodeList.at(node2)[node1] = value;
}

int main()
{
  UndirectedGraph g(5, 0.2, pair<double, double>(1.0, 10.0));

  return 0;
}

