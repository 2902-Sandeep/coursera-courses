// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// DisjointSet.hpp

#ifndef _HW4_DISJOINT_SET_H_
#define _HW4_DISJOINT_SET_H_

#include <unordered_map>

using namespace std;

template <typename T>
class DisjointSet
{
public:
  // Default constructor; creates an empty disjoint set data structure.
  DisjointSet();

  // Destructor.
  ~DisjointSet();

  // Adds an element as its own set; does nothing if the element exists.
  // @param element The element to add.
  void add(T element);

  // Determines if the two given elements are in the same set.
  // @param element1 The first element.
  // @param element2 The second element.
  // @return True if the elements are in the same set, false otherwise.
  bool isConnected(T element1, T element2);

  // Combines the two sets that the given elements belong to into a single set.
  // @param element1 The first element.
  // @param element2 The second element.
  void merge(T element1, T element2);

  // Gets the current number of elements in this disjoint set.
  // @return The number of elements.
  int getNumElements();

  // Gets the current number of sets in this disjoint set.
  // @return The number of sets.
  int getNumSets();

private:
  // Internal representation of a node.
  class Node {
  public:
    Node() : parent(this), rank(0) {} // Default constructor with initialization list.
    Node *parent; // The parent node of this node.
    int rank; // Roughly represents the depth of this node's subtree.
  };

  // The current number of sets.
  int numSets;

  // Stores the unique elements and their associated nodes.
  unordered_map<T, Node*> elements;

  // Finds the representative node of the set that the given node belongs to.
  // @param node The node to check.
  // @return The representative node of the set.
  Node* find(Node *node);

};

// Method definitions placed here to avoid clutter.

template <typename T>
DisjointSet<T>::DisjointSet()
{
  numSets = 0;
}

template <typename T>
DisjointSet<T>::~DisjointSet()
{
  for (auto it = elements.begin(); it != elements.end(); ++it)
    delete it->second;
  elements.clear();
  numSets = 0;
}

template <typename T>
void DisjointSet<T>::add(T element)
{
  if (elements.count(element) > 0) return; // element already exists

  elements[element] = new Node();
  numSets++;
}

template <typename T>
bool DisjointSet<T>::isConnected(T element1, T element2)
{
  return find(elements[element1]) == find(elements[element2]);
}

template <typename T>
void DisjointSet<T>::merge(T element1, T element2)
{
  Node *root1 = find(elements[element1]);
  Node *root2 = find(elements[element2]);
  if (root1 == root2) return; // already in the same set

  // merge the smaller tree into the larger tree (union by rank)
  if (root1->rank > root2->rank)
    root2->parent = root1;
  else if (root2->rank > root1->rank)
    root1->parent = root2;
  else { // if they are the same rank, increment the rank
    root2->parent = root1;
    root1->rank += 1;
  }

  numSets--;
}

template <typename T>
inline int DisjointSet<T>::getNumElements()
{
  return elements.size();
}

template <typename T>
inline int DisjointSet<T>::getNumSets()
{
  return numSets;
}

template <typename T>
typename DisjointSet<T>::Node* DisjointSet<T>::find(Node *node)
{
  // recursively follows the parent node until it reaches the root;
  // simultaneously flattens the tree structure (path compression) for optimization
  if (node->parent != node)
    node->parent = find(node->parent);
  return node->parent;
}

#endif // _HW4_DISJOINT_SET_H_

