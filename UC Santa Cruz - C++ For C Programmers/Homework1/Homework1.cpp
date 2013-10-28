// UC Santa Cruz C++ For C Programmers
// Homework 1: Convert a C program to C++
// TH Hee
// Cumulative sum from 0 to N-1

#include <iostream>
#include <vector>

using namespace std;
const int N = 40;

inline void sum(int &p, vector<int> &d)
{
  p = 0; // initialize the cumulative sum
  for (vector<int>::iterator it = d.begin(); it != d.end(); ++it) // iterate the vector
    p = p + *it; // accumulate each consecutive element in the vector
}

int main()
{
  int accum = 0; // will hold the accumulated result
  vector<int> data; // empty vector of ints

  for (int i = 0; i < N; ++i) // local declaration of i
    data.push_back(i); // adds elements to the end of the vector
  sum(accum, data); // compute the sum of the elements in the vector
  cout << "sum is " << accum << endl; // display the result
  return 0;
}

