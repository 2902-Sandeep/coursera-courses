// UC Santa Cruz C++ For C Programmers
// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// TH Hee
// Main.cpp
// Runs Prim's or Kruskal's algorithm on a graph specified from an input file.

#include <iostream>
#include <numeric>

#include "UndirectedGraph.hpp"

using namespace std;

int main()
{
  UndirectedGraph graph("SampleTestData.txt");
  vector<pair<int, int>> edges;
  vector<double> cost;

  graph.runPrimAlgorithm(edges, cost);

  cout << "Total cost: " << accumulate(cost.begin(), cost.end(), 0.0) << endl;
  for (int i = 0; i < edges.size(); ++i)
    cout << edges[i].first << " -> " << edges[i].second << " (" << cost[i] << ")" << endl;

  return 0;
}

