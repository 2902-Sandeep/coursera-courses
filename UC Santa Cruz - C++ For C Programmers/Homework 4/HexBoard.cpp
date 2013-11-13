// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexBoard.cpp

#include "HexBoard.hpp"

HexBoard::HexBoard(const int size)
{
  // limit the range of board sizes
  if (size < 2) this->size = 2;
  else if (size > 26) this->size = 26;
  else this->size = size;

  // assign the appropriate regular expressions
  pattern1.assign("^([a-zA-Z])([0-9]+)$");
  pattern2.assign("^([0-9]+)([a-zA-Z])$");

  // set up the nodes
  int numNodes = this->size * this->size;
  board.addNodes(numNodes);

  // set up the edges
  for (int i = 0; i < numNodes; ++i) {
    if (i % this->size != this->size - 1) // horizontal connections
      board.addEdge(i, i + 1, 1.0);
    if (i < this->size * (this->size - 1)) { // right-slanted connections
      board.addEdge(i, i + this->size, 1.0);
      if (i % this->size != 0) // left-slanted connections
        board.addEdge(i, i + this->size - 1, 1.0);
    }
  }

  reset();
}

void HexBoard::reset()
{
  for (int i = 0; i < board.getNumNodes(); ++i)
    board.setNodeValue(i, 0.0);
}

int HexBoard::check(const string &position)
{
  smatch match;
  string alpha, num;

  if (regex_search(position, match, pattern1)) { // alphabet comes first
    alpha = match[1];
    num = match[2];
  }
  else if (regex_search(position, match, pattern2)) { // number comes first
    alpha = match[2];
    num = match[1];
  }
  else // no match
    return -1;

  int xIndex = toupper(alpha[0]) - 65; // difference in ASCII value with 'A'
  int yIndex = stoi(num) - 1; // convert to zero-based starting index

  if ((xIndex > size - 1) || (yIndex > size - 1))
    return -1;

  return xIndex + yIndex * size;
}

void HexBoard::set(HexBoardState state, int index)
{

}

HexBoardState HexBoard::get(int index)
{
  return HexBoardState::NONE;
}

void HexBoard::draw()
{

}

