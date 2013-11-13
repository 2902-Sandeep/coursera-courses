// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexBoard.hpp

#ifndef _HW4_HEX_BOARD_H_
#define _HW4_HEX_BOARD_H_

#include <iostream>
#include <string>
#include <regex>
#include <cctype>

#include "UndirectedGraph.hpp"

using namespace std;

// Only 3 possible states for each cell on the hex board.
enum class HexBoardState : char { NONE, X, O };

class HexBoard
{
public:
  // Constructor. Generates a size x size hex board.
  // @param size The size of the hex board; ranging from 2 to 26.
  HexBoard(const int size);

  // Resets the hex board such that there are no pieces in play;
  // i.e. make all states on the board NONE.
  void reset();

  // Checks if the given cell position is valid on this hex board.
  // @param position The alphanumeric cell location to check.
  // @return The index of the cell position; -1 if invalid.
  int check(const string &position);

  // Sets the given state at the specified cell index on the hex board.
  // The cell index starts from 0 at the top left and runs to n at the bottom right.
  // @param state The state to set.
  // @param index A valid cell index on the board returned by the check method.
  void set(HexBoardState state, int index);

  // Gets the state of the specified cell index on the hex board.
  // The cell index starts from 0 at the top left and runs to n at the bottom right.
  // @param index A valid cell index on the board returned by the check method.
  // @return The state of the specified cell index on the hex board.
  HexBoardState get(int index);

  // Draw the formatted hex board onto the console screen.
  void draw();

private:
  // The game board, represented by an undirected graph.
  UndirectedGraph board;

  // The size of the board.
  int size;

  // The regular expression that checks for the pattern where
  // the alphabet comes first, e.g. a6, b11, C2, etc.
  regex pattern1;

  // The regular expression that checks for the pattern where
  // the number comes first, e.g. 8A, 14b, 1c, etc.
  regex pattern2;

};

#endif // _HW4_HEX_BOARD_H_

