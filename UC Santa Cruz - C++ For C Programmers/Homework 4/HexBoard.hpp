// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexBoard.hpp

#ifndef _HW4_HEX_BOARD_H_
#define _HW4_HEX_BOARD_H_

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <cctype>

#include "UndirectedGraph.hpp"

using namespace std;

// Only 3 possible states for each cell on the hex board.
enum class HexBoardPiece : char { X, O, NONE };

class HexBoard
{
public:
  // Default constructor.
  HexBoard();

  // Constructor. Generates a size x size hex board.
  // @param size The size of the hex board; ranging from 2 to 26.
  HexBoard(const int size);

  // Used to initialize a size x size hex board if the default constructor was used.
  // @param size The size of the hex board; ranging from 2 to 26.
  void init(const int size);

  // Resets the hex board such that there are no pieces in play;
  // i.e. make all states on the board NONE.
  void reset();

  // Gets the number of hexes on one side of the board.
  // @return The size of the board.
  int getSize();

  // Checks if the given cell position is valid on this hex board.
  // @param position The alphanumeric cell location to check.
  // @return The index of the cell position; -1 if invalid.
  int check(const string &position);

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

private:
  // The game board, represented by an undirected graph.
  // The nodes have enum states, and the edges are integer values.
  UndirectedGraph<HexBoardPiece, int> board;

  // The size of the board.
  int size;

  // The regular expression that checks for the pattern where
  // the alphabet comes first, e.g. a6, b11, C2, etc.
  regex pattern1;

  // The regular expression that checks for the pattern where
  // the number comes first, e.g. 8A, 14b, 1c, etc.
  regex pattern2;

  // Internal function used to initialize the regular expressions.
  void initRegex();

};

// Inline function definitions placed here to avoid linker errors.

inline int HexBoard::getSize()
{
  return size;
}

inline void HexBoard::set(const HexBoardPiece state, const int index)
{
  board.setNodeValue(index, state);
}

inline HexBoardPiece HexBoard::get(const int index)
{
  return board.getNodeValue(index);
}

inline void HexBoard::getNeighbors(const int index, vector<int> &neighbors)
{
  board.getNeighbors(index, neighbors);
}

#endif // _HW4_HEX_BOARD_H_

