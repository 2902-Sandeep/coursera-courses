// Testing framework for the UndirectedGraph class.

#include <iostream>
#include <algorithm>
#include <utility>

#include "UndirectedGraph.hpp"
#include "CustomAssert.hpp"

enum class NodeColor : char { BLACK, WHITE };
enum class EdgeColor : char { RED, GREEN, BLUE };

void UndirectedGraph_TestInitialization()
{
  std::cerr << "Running Test for Node Sanity..." << std::endl;

  UndirectedGraph<int, int> testIntInt;
  testIntInt.init(0, 0);
  ASSERT_CONDITION(testIntInt.getNumNodes() == 0, "Graph initialization check");
  ASSERT_CONDITION(testIntInt.getNumEdges() == 0, "Graph initialization check");

  UndirectedGraph<double, double> testDoubleDouble(0.0, 0.0);
  ASSERT_CONDITION(testDoubleDouble.getNumNodes() == 0, "Graph initialization check");
  ASSERT_CONDITION(testDoubleDouble.getNumEdges() == 0, "Graph initialization check");

  UndirectedGraph<NodeColor, EdgeColor> testCustomEnum;
  testCustomEnum.init(NodeColor::WHITE, EdgeColor::BLUE);
  ASSERT_CONDITION(testCustomEnum.getNumNodes() == 0, "Graph initialization check");
  ASSERT_CONDITION(testCustomEnum.getNumEdges() == 0, "Graph initialization check");

  testCustomEnum.addNodes(5);
  testCustomEnum.addNodes(5, NodeColor::BLACK);

  ASSERT_CONDITION(testCustomEnum.getNumNodes() == 10, "Graph initialization check");
  for (int i = 0; i < 5; ++i)
    ASSERT_CONDITION(testCustomEnum.getNodeValue(i) == NodeColor::WHITE, "Default node addition check");
  for (int i = 5; i < 10; ++i)
    ASSERT_CONDITION(testCustomEnum.getNodeValue(i) == NodeColor::BLACK, "Explicit node addition check");
}
/*
// Helper function to count edges based on adjacency.
int countEdges(UndirectedGraph &g)
{
  int count = 0;
  for (int i = 0; i < g.getNumNodes(); i++) {
    for (int j = 0; j < g.getNumNodes(); j++) {
      count += g.isAdjacent(i, j) ? 1 : 0;
    }
  }
  return count / 2;
}

void UndirectedGraph_TestAdjacency()
{
  std::cerr << "Running Test for Adjacency..." << std::endl;

  // Full graph.
  UndirectedGraph test1(100, 1.0, std::pair<double, double>(1.0, 1.0));
  ASSERT_CONDITION_SHOW_PASS(countEdges(test1) == 100 * (100 - 1) / 2, "Complete graph adjacency count check");
  vector<int> neighbors;
  for (int i = 0; i < 100; i++) {
    test1.getNeighbors(i, neighbors);
    ASSERT_CONDITION(neighbors.size() == 99, "Neighbor count check");
    int j = 0;
    while (j < 100) {
      if (j != i)
        ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), j) != neighbors.end(), "Neighbor correctness check");
      j++;
    }
  }

  // Empty graph.
  UndirectedGraph test2(100, 0.0, std::pair<double, double>(1.0, 1.0));
  ASSERT_CONDITION_SHOW_PASS(countEdges(test2) == 0, "Graph with no edges adjacency count check");

  // Graph with some edges added.
  for (int i = 25; i < 75; i++)
    test2.addEdge(0, i, 1.0);
  ASSERT_CONDITION_SHOW_PASS(countEdges(test2) == 50, "Edges added: adjacency count check");
  test2.getNeighbors(0, neighbors);
  ASSERT_CONDITION_SHOW_PASS(neighbors.size() == 50, "Edges added: neighbor count check");
  for (int i = 25; i < 75; i++)
    ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), i) != neighbors.end(), "Edges added: neighbor correctness check");
  ASSERT_CONDITION_SHOW_PASS(test2.getNumEdges() == 50, "Edges added: edge count check");

  for (int i = 0; i < 100; i++) {
    if (i >= 25 && i < 75) {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == true, "Edges added: connected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == true, "Edges added: connected nodes adjacency test, reversed");
    }
    else {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == false, "Edges added: unconnected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == false, "Edges added: unconnected nodes adjacency test, reversed");
    }
  }

  // Graph with some edges deleted.
  for (int i = 35; i < 65; i++)
    test2.deleteEdge(0, i);
  ASSERT_CONDITION_SHOW_PASS(countEdges(test2) == 20, "Edges deleted: adjacency count check");
  test2.getNeighbors(0, neighbors);
  ASSERT_CONDITION_SHOW_PASS(neighbors.size() == 20, "Edged deleted: neighbor count check");
  for (int i = 25; i < 35; i++)
    ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), i) != neighbors.end(), "Edges deleted: neighbor correctness check 1");
  for (int i = 65; i < 75; i++)
    ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), i) != neighbors.end(), "Edges deleted: neighbor correctness check 2");
  ASSERT_CONDITION_SHOW_PASS(test2.getNumEdges() == 20, "Edges deleted: edge count check");

  for (int i = 0; i < 100; i++) {
    if ((i >= 25 && i < 35) || (i >= 65 && i < 75)) {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == true, "Edges deleted: connected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == true, "Edges deleted: connected nodes adjacency test, reversed");
    }
    else {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == false, "Edges deleted: unconnected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == false, "Edges deleted: unconnected nodes adjacency test, reversed");
    }
  }
}
*/

int main()
{
  UndirectedGraph_TestInitialization();
/*
  UndirectedGraph_TestAdjacency();
*/
  return 0;
}

