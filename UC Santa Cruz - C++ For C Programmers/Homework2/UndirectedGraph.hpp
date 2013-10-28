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
#include <chrono>
#include <random>

using namespace std;

class UndirectedGraph
{
public:
  // Constructor.
  UndirectedGraph(double density, double minDistance, double maxDistance);

  // Destructor.
  ~UndirectedGraph();

  // Returns the number of vertices in the graph.
  inline int get_num_vertices();

  // Returns the number of edges in the graph.
  inline int get_num_edges();

  // Test if there is an edge between two vertices.
  inline bool is_adjacent(int v1, int v2);

  // List all connected vertices to the given vertex.
  void neighbors(int v);

  // Adds an edge between the two vertices, if it is not there.
  inline void add_edge(int v1, int v2);

  // Delete the edge between the two vertices, if it is there.
  inline void delete_edge(int v1, int v2);

  // Returns the value associated with the vertex.
  inline double get_vertex_value(int v);

  // Sets the value associated with the vertex.
  inline void set_vertex_value(int v, double value);

  // Returns the value associated with the edge between the two vertices.
  inline double get_edge_value(int v1, int v2);

  // Sets the value associated with the edge between the two vertices.
  inline void set_edge_value(int v1, int v2, double value);

private:
  // The number of vertices in this undirected graph.
  const int numVertices = 10;

  // The number of edges in this undirected graph.
  int numEdges;

  // The adjacency list representing this graph.
  vector<pair<double, unordered_map<int, double>>> vertices;

};

#endif // _HW2_UNDIRECTED_GRAPH_H_

