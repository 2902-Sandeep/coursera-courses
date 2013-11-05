// Testing framework for the PriorityQueue class.

#include <iostream>

#include "PriorityQueue.hpp"
#include "CustomAssert.hpp"

int main()
{
  PriorityQueue<int, int> pq;

  for (int i = 0, j = 9; i < 10; i++, j--) {
    pq.push(i, j);
    ASSERT_CONDITION(pq.top() == 0, "Highest priority check");
  }

  ASSERT_CONDITION(pq.size() == 10, "Size check");

  for (int i = 0; i < 10; i++)
    ASSERT_CONDITION(pq.contains(i) == true, "Existence check");

  pq.changePriority(4, 100);
  ASSERT_CONDITION(pq.top() == 4, "Change priority check");
  pq.changePriority(4, 5);

  for (int i = 0; i < 10; i++) {
    ASSERT_CONDITION(pq.top() == i, "Top check");
    ASSERT_CONDITION(pq.pop() == i, "Pop check");
  }

  ASSERT_CONDITION(pq.size() == 0, "Empty check");

  return 0;
}

