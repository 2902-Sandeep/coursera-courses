// Testing framework for the UndirectedGraph class.

#include <cassert>
#include <iostream>
#include <algorithm>
#include <utility>

#include "UndirectedGraph.hpp"

void UndirectedGraph_TestNodeSanity()
{
  std::cerr << "Running Test for Node Sanity...";

  for (int i = 0; i < 100; i++) {
    UndirectedGraph test(i, 0.0, std::pair<double, double>(0.0, 0.0));
    assert(test.getNumNodes() == i);
  }

  std::cerr << "passed!" << std::endl;
}

void UndirectedGraph_TestDensitySanity()
{
  std::cerr << "Running Test for Density Sanity...";

  UndirectedGraph test1(100, 0.0, std::pair<double, double>(0.0, 0.0));
  assert(test1.getNumEdges() == 0);

  UndirectedGraph test2(100, 1.0, std::pair<double, double>(0.0, 0.0));
  assert(test2.getNumEdges() == 100 * (100 - 1) / 2);

  for (double i = 0.01; i < 1.00; i += 0.01) {
    UndirectedGraph test(100, 0.0, std::pair<double, double>(0.0, 0.0));
    assert(test.getNumEdges() >= 0);
    assert(test.getNumEdges() <= 100 * (100 - 1) / 2);
  }

  std::cerr << "passed!" << std::endl;
}

void UndirectedGraph_TestEdgeDistanceSanity()
{
  std::cerr << "Running Test for Edge Distance Sanity...";

  for (double i = 1.0; i < 10.0; i += 0.1) {
    UndirectedGraph test(100, 1.0, std::pair<double, double>(i, 10.0));
    for (int j = 0; j < 100; j++) {
      for (int k = 0; k < 100; k++) {
        if (test.isAdjacent(j, k)) {
          assert(test.getEdgeValue(j, k) >= i);
          assert(test.getEdgeValue(j, k) <= 10.0);
        }
      }
    }
  }

  for (double i = 10.0; i > 1.0; i -= 0.1) {
    UndirectedGraph test(100, 1.0, std::pair<double, double>(1.0, i));
    for (int j = 0; j < 100; j++) {
      for (int k = 0; k < 100; k++) {
        if (test.isAdjacent(j, k)) {
          assert(test.getEdgeValue(j, k) >= 1.0);
          assert(test.getEdgeValue(j, k) <= i);
        }
      }
    }
  }

  std::cerr << "passed!" << std::endl;
}

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
  std::cerr << "Running Test for Adjacency...";

  UndirectedGraph test1(100, 1.0, std::pair<double, double>(0.0, 0.0));
  assert(countEdges(test1) == 100 * (100 - 1) / 2);
  for (int i = 0; i < 100; i++) {
    vector<int> neighbors = test1.getNeighbors(i);
    assert(neighbors.size() == 99);
    int j = 0;
    while (j < 100) {
      if (j != i)
        assert(find(neighbors.begin(), neighbors.end(), j) != neighbors.end());
      j++;
    }
  }

  UndirectedGraph test2(100, 0.0, std::pair<double, double>(0.0, 0.0));
  assert(countEdges(test2) == 0);

  for (int i = 25; i < 75; i++)
    test2.addEdge(0, i);

  assert(countEdges(test2) == 50);
  vector<int> neighbors = test2.getNeighbors(0);
  assert(neighbors.size() == 50);
  for (int i = 25; i < 75; i++)
    assert(find(neighbors.begin(), neighbors.end(), i) != neighbors.end());
  assert(test2.getNumEdges() == 50);

  for (int i = 0; i < 100; i++) {
    if (i >= 25 && i < 75) {
      assert(test2.isAdjacent(0, i) == true);
      assert(test2.isAdjacent(i, 0) == true);
    }
    else {
      assert(test2.isAdjacent(0, i) == false);
      assert(test2.isAdjacent(i, 0) == false);
    }
  }

  for (int i = 35; i < 65; i++)
    test2.deleteEdge(0, i);

  assert(countEdges(test2) == 20);
  neighbors = test2.getNeighbors(0);
  assert(neighbors.size() == 20);
  for (int i = 25; i < 35; i++)
    assert(find(neighbors.begin(), neighbors.end(), i) != neighbors.end());
  for (int i = 65; i < 75; i++)
    assert(find(neighbors.begin(), neighbors.end(), i) != neighbors.end());
  assert(test2.getNumEdges() == 20);

  for (int i = 0; i < 100; i++) {
    if ((i >= 25 && i < 35) || (i >=65 && i < 75)) {
      assert(test2.isAdjacent(0, i) == true);
      assert(test2.isAdjacent(i, 0) == true);
    }
    else {
      assert(test2.isAdjacent(0, i) == false);
      assert(test2.isAdjacent(i, 0) == false);
    }
  }

  std::cerr << "passed!" << std::endl;
}

int main()
{
  UndirectedGraph_TestNodeSanity();
  UndirectedGraph_TestDensitySanity();
  UndirectedGraph_TestEdgeDistanceSanity();

  UndirectedGraph_TestAdjacency();

  return 0;
}

