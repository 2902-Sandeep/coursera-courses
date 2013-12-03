// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexBoard.cpp

#include "HexBoard.hpp"

HexBoard::HexBoard(const int size)
  : board(HexBoardPiece::NONE, 0) // initialize the graph with defaults
{
  // limit the range of board sizes
  this->size = max(2, min(size, 26));

  // set up the nodes
  int numNodes = this->size * this->size;
  board.addNodes(numNodes);

  // set up the edges
  for (int i = 0; i < numNodes; ++i) {
    indicesN.insert(i); // initialize the set of unoccupied cells
    if (i % this->size != this->size - 1) // horizontal connections
      board.addEdge(i, i + 1, 1);
    if (i < this->size * (this->size - 1)) { // right-slanted connections
      board.addEdge(i, i + this->size, 1);
      if (i % this->size != 0) // left-slanted connections
        board.addEdge(i, i + this->size - 1, 1);
    }
  }
}

void HexBoard::reset()
{
  indicesX.clear();
  indicesO.clear();

  for (int i = 0; i < board.getNumNodes(); ++i) {
    indicesN.insert(i); // reinitialize the set of unoccupied cells
    board.setNodeValue(i, HexBoardPiece::NONE);
  }
}

int HexBoard::check(const string &position)
{
  int xIndex, yIndex;

  if (position.size() == 2 || position.size() == 3) {
    int endIdx = position.size() - 1;
    if (isalpha(position[0]) && isNumber(position.substr(1, endIdx))) {
      xIndex = getX(position[0]);
      yIndex = getY(position.substr(1, endIdx));
    }
    else if (isalpha(position[endIdx]) && isNumber(position.substr(0, endIdx))) {
      xIndex = getX(position[endIdx]);
      yIndex = getY(position.substr(0, endIdx));
    }
    else
      return -1;
  }
  else
    return -1;

  if ((xIndex > size - 1) || (yIndex > size - 1))
    return -1;

  return xIndex + yIndex * size;
}

int HexBoard::check(const int boardIndex)
{
  return (boardIndex >= 0) && (boardIndex < board.getNumNodes()) ? boardIndex : -1;
}

void HexBoard::set(const HexBoardPiece state, const int index)
{
  if (state != board.getNodeValue(index)) { // we are changing states
    // remove from appropriate set
    switch (board.getNodeValue(index)) {
    case HexBoardPiece::NONE:
      indicesN.erase(index); break;
    case HexBoardPiece::X:
      indicesX.erase(index); break;
    case HexBoardPiece::O:
      indicesO.erase(index); break;
    }

    // insert into appropriate set
    switch (state) {
    case HexBoardPiece::NONE:
      indicesN.insert(index); break;
    case HexBoardPiece::X:
      indicesX.insert(index); break;
    case HexBoardPiece::O:
      indicesO.insert(index); break;
    }
  }

  board.setNodeValue(index, state);
}

void HexBoard::draw()
{
  // display first row of letters
  cout << "  ";
  for (int i = 0; i < size; ++i) cout << " " << static_cast<char>(65 + i);
  cout << endl;

  // display main hex grid
  for (int y = 0; y < size; ++y) {
    // display variable initial spacing
    cout << string(y, ' ');

    // display number (left side)
    if (y < 9) cout << " " << y + 1 << " ";
    else cout << y + 1 << " ";

    // display grid row
    for (int x = 0; x < size; ++x) {
      switch (board.getNodeValue(x + y * size)) {
      case HexBoardPiece::X:
        cout << " x";
        break;
      case HexBoardPiece::O:
        cout << " o";
        break;
      case HexBoardPiece::NONE:
      default:
        cout << " .";
        break;
      }
    }

    // display number (right side)
    cout << "  " << y + 1 << endl;
  }

  // display last row of letters
  cout << "   " << string(size, ' ');
  for (int i = 0; i < size; ++i) cout << " " << static_cast<char>(65 + i);
  cout << endl;
}

void HexBoard::getUnoccupiedCellIndices(vector<int> &indices)
{
  indices.assign(indicesN.begin(), indicesN.end());
}

void HexBoard::getOccupiedCellIndices(vector<int> &indices)
{
  indices.clear();
  indices.insert(indices.end(), indicesX.begin(), indicesX.end());
  indices.insert(indices.end(), indicesO.begin(), indicesO.end());
}

void HexBoard::getXCellIndices(vector<int> &indices)
{
  indices.assign(indicesX.begin(), indicesX.end());
}

void HexBoard::getOCellIndices(vector<int> &indices)
{
  indices.assign(indicesO.begin(), indicesO.end());
}

