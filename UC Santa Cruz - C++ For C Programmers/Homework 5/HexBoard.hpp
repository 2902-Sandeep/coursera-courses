// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexBoard.hpp

#ifndef _HW5_HEX_BOARD_H_
#define _HW5_HEX_BOARD_H_

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
#include <cctype>

#include "UndirectedGraph.hpp"

using namespace std;

// Only 3 possible states for each cell on the hex board.
enum class HexBoardPiece : char { X, O, NONE };

class HexBoard
{
public:
  // Constructor. Generates a size x size hex board.
  // @param size The size of the hex board; ranging from 2 to 26.
  HexBoard(const int size);

  // Resets the hex board such that there are no pieces in play;
  // i.e. make all states on the board NONE.
  void reset();

  // Gets the number of hexes on one side of the board.
  // @return The size of the board.
  int getSize();

  // Gets the total number of hexes on the board.
  // @return The number of hexes on the board.
  int getNumCells();

  // Checks if the given cell position is valid on this hex board.
  // @param position The alphanumeric cell location to check.
  // @return The index of the cell position; -1 if invalid.
  int check(const string &position);
  // @param boardIndex The zero-based location index on the hex board to check.
  int check(const int boardIndex);

  // Sets the given state at the specified cell index on the hex board.
  // The cell index starts from 0 at the top left and runs to n at the bottom right.
  // @param piece The state to set.
  // @param index A valid cell index on the board returned by the check method.
  void set(const HexBoardPiece piece, const int index);

  // Gets the state of the specified cell index on the hex board.
  // The cell index starts from 0 at the top left and runs to n at the bottom right.
  // @param index A valid cell index on the board returned by the check method.
  // @return The state of the specified cell index on the hex board.
  HexBoardPiece get(const int index);

  // Draw the formatted hex board onto the console screen.
  void draw();

  // Gets the indices of the neighbors of the specified cell index.
  // The cell index starts from 0 at the top left and runs to n at the bottom right.
  // @param index A valid cell index on the board returned by the check method.
  // @param neighbors The reference vector of neighbors returned; any existing content will be cleared.
  void getNeighbors(const int index, vector<int> &neighbors);

  // Gets the indices of all the unoccupied cells.
  // @param indices The reference vector of unoccupied cell indices returned; any existing content will be cleared.
  void getUnoccupiedCellIndices(vector<int> &indices);

  // Gets the indices of all the occupied cells.
  // @param indices The reference vector of occupied cell indices returned; any existing content will be cleared.
  void getOccupiedCellIndices(vector<int> &indices);

  // Gets the indices of all cells occupied with the X piece.
  // @param indices The reference vector of cell indices returned; any existing content will be cleared.
  void getXCellIndices(vector<int> &indices);

  // Gets the indices of all cells occupied with the O piece.
  // @param indices The reference vector of cell indices returned; any existing content will be cleared.
  void getOCellIndices(vector<int> &indices);

private:
  // The game board, represented by an undirected graph.
  // The nodes have enum states, and the edges are integer values.
  UndirectedGraph<HexBoardPiece, int> board;

  // The size of the board (length of one side).
  int size;

  // The cell indices that are unoccupied (HexBoardPiece::NONE).
  std::set<int> indicesN;

  // The cell indices that are occupied with HexBoardPiece::X.
  std::set<int> indicesX;

  // The cell indices that are occupied with HexBoardPiece::O.
  std::set<int> indicesO;

  // Determines if the given string is a positive integral number.
  // @param s The string to check.
  // @return True if the string represents a number, otherwise false.
  bool isNumber(const string &s);

  // Get the x-index corresponding to the given alphabet.
  // @param c The alphabet to convert.
  // @return The corresponding x-index on the board.
  int getX(const char c);

  // Get the y-index corresponding to the given number string.
  // @param s The number string to convert.
  // @return The corresponding y-index on the board.
  int getY(const string &s);

};

// Inline function definitions placed here to avoid linker errors.

inline int HexBoard::getSize()
{
  return size;
}

inline int HexBoard::getNumCells()
{
  return size * size;
}

inline HexBoardPiece HexBoard::get(const int index)
{
  return board.getNodeValue(index);
}

inline void HexBoard::getNeighbors(const int index, vector<int> &neighbors)
{
  board.getNeighbors(index, neighbors);
}

inline bool HexBoard::isNumber(const string &s)
{
  return find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

inline int HexBoard::getX(const char c)
{
  return toupper(c) - 'A'; // difference in ASCII value
}

inline int HexBoard::getY(const string &s)
{
  return stoi(s) - 1; // convert to zero-based starting index
}

#endif // _HW5_HEX_BOARD_H_

