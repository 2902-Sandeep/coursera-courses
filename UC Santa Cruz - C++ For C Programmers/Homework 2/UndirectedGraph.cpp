#include "UndirectedGraph.hpp"

UndirectedGraph::UndirectedGraph(double density, double minDistance, double maxDistance)
{
  for (int i = 0; i < numVertices; i++)
    vertices.push_back(pair<double, unordered_map<int, double>>(0.0, unordered_map<int, double>()));

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  uniform_real_distribution<double> densityDistribution(0.0, 1.0);
  uniform_real_distribution<double> edgeLengthDistribution(1.0, 10.0);

  for (int i = 1; i < numVertices; i++) {
    for (int j = 0; j < i; j++) {
      double densityValue = densityDistribution(generator);
      cout << i << " " << j << " " << densityValue;
      if (densityValue < density) {
        add_edge(j, i);
        double edgeLength = edgeLengthDistribution(generator);
        set_edge_value(j, i, edgeLength);
        cout << " edge length: " << edgeLength;
      }
      cout << endl;
    }
  }
}

UndirectedGraph::~UndirectedGraph()
{

}

inline int UndirectedGraph::get_num_vertices()
{
  return numVertices;
}

inline int UndirectedGraph::get_num_edges()
{
  return numEdges;
}

inline bool UndirectedGraph::is_adjacent(int v1, int v2)
{
  return vertices.at(v1).second.find(v2) != vertices.at(v1).second.end();
}

void UndirectedGraph::neighbors(int v)
{
  cout << "vertex " << v << " is connected to:";
  for (auto it = vertices.at(v).second.begin(); it != vertices.at(v).second.end(); ++it)
    cout << " " << it->first;
  cout << endl;
}

inline void UndirectedGraph::add_edge(int v1, int v2)
{
  vertices.at(v1).second[v2] = 0.0;
  vertices.at(v2).second[v1] = 0.0;
}

inline void UndirectedGraph::delete_edge(int v1, int v2)
{
  vertices.at(v1).second.erase(v2);
  vertices.at(v2).second.erase(v1);
}

inline double UndirectedGraph::get_vertex_value(int v)
{
  return vertices.at(v).first;
}

inline void UndirectedGraph::set_vertex_value(int v, double value)
{
  vertices.at(v).first = value;
}

inline double UndirectedGraph::get_edge_value(int v1, int v2)
{
  return vertices.at(v1).second[v2];
}

inline void UndirectedGraph::set_edge_value(int v1, int v2, double value)
{
  vertices.at(v1).second[v2] = value;
  vertices.at(v2).second[v1] = value;
}

int main()
{
  UndirectedGraph g(0.2, 1.0, 10.0);

  return 0;
}

