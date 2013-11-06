// Testing framework for the ShortestPath class.

#include <iostream>
#include <list>
#include <utility>
#include <limits>

#include "UndirectedGraph.hpp"
#include "ShortestPath.hpp"
#include "CustomAssert.hpp"

void ShortestPath_TestSimpleConnectedGraph()
{
  std::cerr << "Running Test for Simple Connected Graph..." << std::endl;

  UndirectedGraph g(6, 0.0, std::pair<double, double>(0.0, 0.0));
  g.addEdge(0, 1, 7.0);
  g.addEdge(0, 2, 9.0);
  g.addEdge(0, 5, 14.0);
  g.addEdge(1, 2, 10.0);
  g.addEdge(1, 3, 15.0);
  g.addEdge(2, 3, 11.0);
  g.addEdge(2, 5, 2.0);
  g.addEdge(3, 4, 6.0);
  g.addEdge(4, 5, 9.0);

  ShortestPath p(g, 0, 0);
  std::list<int> l;

  ASSERT_CONDITION(p.pathCost() == 0.0, "Start equals end cost check");
  ASSERT_CONDITION(p.exists() == true, "Start equals end existence check");
  l = p.path();
  ASSERT_CONDITION(l.front() == 0, "Start equals end path check"); l.pop_front();
  ASSERT_CONDITION(l.front() == 0, "Start equals end path check"); l.pop_front();
  ASSERT_CONDITION(l.size() == 0, "Start equals end path check");

  p.updateGraph(g, 0, 4);

  ASSERT_CONDITION(p.pathCost() == 20.0, "Simple connected graph cost check");
  ASSERT_CONDITION(p.exists() == true, "Simple connected graph existence check");
  l = p.path();
  ASSERT_CONDITION(l.front() == 0, "Simple connected graph path check"); l.pop_front();
  ASSERT_CONDITION(l.front() == 2, "Simple connected graph path check"); l.pop_front();
  ASSERT_CONDITION(l.front() == 5, "Simple connected graph path check"); l.pop_front();
  ASSERT_CONDITION(l.front() == 4, "Simple connected graph path check"); l.pop_front();
  ASSERT_CONDITION(l.size() == 0, "Simple connected graph path check");
}

void ShortestPath_TestUnconnectedGraph()
{
  std::cerr << "Running Test for Unconnected Graph..." << std::endl;

  UndirectedGraph g(6, 0.0, std::pair<double, double>(0.0, 0.0));
  g.addEdge(0, 1, 7.0);
  g.addEdge(0, 2, 9.0);
  g.addEdge(0, 5, 14.0);
  g.addEdge(1, 2, 10.0);
  g.addEdge(2, 5, 2.0);
  g.addEdge(3, 4, 6.0);

  ShortestPath p(g, 0, 4);
  ASSERT_CONDITION(p.pathCost() == std::numeric_limits<double>::max(), "Unconnected graph cost check");
  ASSERT_CONDITION(p.exists() == false, "Unconnected graph existence check");
  ASSERT_CONDITION(p.path().size() == 0, "Unconnected graph path check");
}

int main()
{
  ShortestPath_TestSimpleConnectedGraph();
  ShortestPath_TestUnconnectedGraph();

  return 0;
}

