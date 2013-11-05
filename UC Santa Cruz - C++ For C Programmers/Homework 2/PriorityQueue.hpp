// UC Santa Cruz C++ For C Programmers
// Homework 2: Implement Dijkstra's Algorithm
// TH Hee
// PriorityQueue.hpp

#ifndef _HW2_PRIORITY_QUEUE_H_
#define _HW2_PRIORITY_QUEUE_H_

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T1, typename T2>
class PriorityQueue
{
public:
  // Constructor; creates a priority queue with elements of type T.
  PriorityQueue()
  {

  }

  // Access the top element in this priority queue.
  // @return Returns the element with the highest priority without removing it from the queue.
  inline T1 top()
  {
    return elements.front().first;
  }

  // Remove the top element in this priority queue.
  // @return Removes and returns the element with the highest priority from the queue.
  T1 pop()
  {
    pop_heap(elements.begin(), elements.end(), ComparePair());
    T1 topElement = elements.back().first;
    elements.pop_back();
    return topElement;
  }

  // Insert an element into this priority queue.
  // @param element The element to insert into the queue.
  // @param priority The priority of the element.
  void push(T1 element, T2 priority)
  {
    elements.push_back(pair<T1, T2>(element, priority));
    push_heap(elements.begin(), elements.end(), ComparePair());
  }

  // Gets the size of this priority queue.
  // @return The number of elements in the queue.
  inline int size()
  {
    return elements.size();
  }

  // Tests if the priority queue is empty.
  // @return True if the priority queue is empty, otherwise false.
  inline bool empty()
  {
    return elements.empty();
  }

  // Clears the contents of the priority queue.
  inline void clear()
  {
    elements.clear();
  }

  // Checks for the first occurrence of a specific element in the the queue.
  // @param element The element whose existence in the queue is to be determined.
  // @return True if the element exists, false otherwise.
  inline bool contains(T1 element)
  {
    return find_if(elements.begin(), elements.end(), FindFirst(element)) != elements.end();
  }

  // Changes the priority of the first occurrence of a specific element.
  // @param element The element whose priority we wish to change.
  // @param priority The new priority of the element.
  void changePriority(T1 element, T2 priority)
  {
    typename vector<std::pair<T1, T2> >::iterator it = find_if(elements.begin(), elements.end(), FindFirst(element));
    if (it != elements.end()) {
      (*it).second = priority;
      make_heap(elements.begin(), elements.end(), ComparePair());
    }
  }

private:
  // The vector of elements in this queue; the first item in the pair is
  // the actual element of type T, while the second item is the priority.
  vector<pair<T1, T2>> elements;

  class ComparePair
  {
  public:
    bool operator()(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
      return lhs.second > rhs.second;
    }
  };

  class FindFirst
  {
  public:
    FindFirst(T1 item) : item(item) {}

    bool operator()(const pair<T1, T2> &elem)
    {
      return item == elem.first;
    }

  private:
    T1 item;
  };

};

#endif // _HW2_PRIORITY_QUEUE_H_

