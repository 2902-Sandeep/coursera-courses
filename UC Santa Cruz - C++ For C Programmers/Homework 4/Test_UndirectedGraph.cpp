// Testing framework for the UndirectedGraph class.

#include <iostream>
#include <algorithm>
#include <utility>

#include "UndirectedGraph.hpp"
#include "CustomAssert.hpp"

enum class NodeColor : char { BLACK, WHITE };
enum class EdgeColor : char { RED, GREEN, BLUE };

// Helper function to count edges based on adjacency.
template <typename T1, typename T2>
int countEdges(UndirectedGraph<T1, T2> &g)
{
  int count = 0;
  for (int i = 0; i < g.getNumNodes(); i++) {
    for (int j = 0; j < g.getNumNodes(); j++) {
      count += g.isAdjacent(i, j) ? 1 : 0;
    }
  }
  return count / 2;
}

void UndirectedGraph_TestInitialization()
{
  std::cerr << "Running Test for Initialization Sanity..." << std::endl;

  UndirectedGraph<int, int> testIntInt;
  testIntInt.init(0, 0);
  ASSERT_CONDITION(testIntInt.getNumNodes() == 0, "Graph initialization check");
  ASSERT_CONDITION(testIntInt.getNumEdges() == 0, "Graph initialization check");

  UndirectedGraph<double, double> testDoubleDouble(0.0, 0.0);
  ASSERT_CONDITION(testDoubleDouble.getNumNodes() == 0, "Graph initialization check");
  ASSERT_CONDITION(testDoubleDouble.getNumEdges() == 0, "Graph initialization check");
}

void UndirectedGraph_TestCustomEnum()
{
  std::cerr << "Running Test for Custom Enum graph..." << std::endl;

  UndirectedGraph<NodeColor, EdgeColor> testCustomEnum;
  testCustomEnum.init(NodeColor::WHITE, EdgeColor::BLUE);
  ASSERT_CONDITION(testCustomEnum.getNumNodes() == 0, "Graph initialization check");
  ASSERT_CONDITION(testCustomEnum.getNumEdges() == 0, "Graph initialization check");

  // Nodes added.
  testCustomEnum.addNodes(5);
  testCustomEnum.addNodes(5, NodeColor::BLACK);

  ASSERT_CONDITION(testCustomEnum.getNumNodes() == 10, "Custom enum graph initialization check");
  ASSERT_CONDITION(testCustomEnum.getNumEdges() == 0, "Custom enum graph initialization check");
  ASSERT_CONDITION(countEdges(testCustomEnum) == 0, "No edge adjacency count check");
  for (int i = 0; i < 5; ++i)
    ASSERT_CONDITION(testCustomEnum.getNodeValue(i) == NodeColor::WHITE, "Default node addition check");
  for (int i = 5; i < 10; ++i)
    ASSERT_CONDITION(testCustomEnum.getNodeValue(i) == NodeColor::BLACK, "Explicit node addition check");

  // Edges added.
  for (int i = 1; i < 10; ++i)
    testCustomEnum.addEdge(0, i);
  for (int i = 2; i < 10; ++i)
    testCustomEnum.addEdge(1, i, EdgeColor::GREEN);

  ASSERT_CONDITION(testCustomEnum.getNumEdges() == 17, "Edge count check");
  ASSERT_CONDITION(countEdges(testCustomEnum) == 17, "Edge count check via adjacency");

  std::vector<int> neighbors;
  testCustomEnum.getNeighbors(1, neighbors);
  ASSERT_CONDITION(neighbors.size() == 9, "Neighbor count check");
  ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), 0) != neighbors.end(), "Neighbor correctness check");
  ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), 1) == neighbors.end(), "Neighbor correctness check");
  for (int i = 2; i < 10; ++i)
    ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), i) != neighbors.end(), "Neighbor correctness check");

  // Edges deleted.
  testCustomEnum.deleteEdge(1, 9);
  testCustomEnum.deleteEdge(0, 9);

  ASSERT_CONDITION(testCustomEnum.getNumEdges() == 15, "Edge count check");
  ASSERT_CONDITION(countEdges(testCustomEnum) == 15, "Edge count check via adjacency");
  testCustomEnum.getNeighbors(1, neighbors);
  ASSERT_CONDITION(neighbors.size() == 8, "Neighbor count check");

  // Node values check.
  for (int i = 0; i < 10; ++i) {
    if (i % 2 == 0) {
      testCustomEnum.setNodeValue(i, NodeColor::WHITE);
      ASSERT_CONDITION(testCustomEnum.getNodeValue(i) == NodeColor::WHITE, "White nodes check");
    }
    else {
      testCustomEnum.setNodeValue(i, NodeColor::BLACK);
      ASSERT_CONDITION(testCustomEnum.getNodeValue(i) == NodeColor::BLACK, "Black nodes check");
    }
  }

  // Edge values check.
  for (int i = 1; i < 9; ++i)
    ASSERT_CONDITION(testCustomEnum.getEdgeValue(0, i) == EdgeColor::BLUE, "Edge correctness check");
  for (int i = 2; i < 9; ++i)
    ASSERT_CONDITION(testCustomEnum.getEdgeValue(1, i) == EdgeColor::GREEN, "Edge correctness check");
  testCustomEnum.setEdgeValue(0, 1, EdgeColor::RED);
  ASSERT_CONDITION(testCustomEnum.getEdgeValue(0, 1) == EdgeColor::RED, "Edge correctness check");
}

int main()
{
  UndirectedGraph_TestInitialization();
  UndirectedGraph_TestCustomEnum();

  return 0;
}

