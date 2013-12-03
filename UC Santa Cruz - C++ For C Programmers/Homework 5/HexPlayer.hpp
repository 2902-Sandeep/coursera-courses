// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexPlayer.hpp

#ifndef _HW5_HEX_PLAYER_H_
#define _HW5_HEX_PLAYER_H_

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>

#include "HexBoard.hpp"
#include "DisjointSet.hpp"

using namespace std;

// Only 3 possible move results.
enum class HexMoveResult : char { VALID, OUTOFBOUNDS, OCCUPIED };

class HexPlayer
{
public:
  // Default constructor.
  HexPlayer(bool isFirstPlayer);

  virtual ~HexPlayer();

  virtual bool makeMove(HexBoard &board, const int turnNum) = 0;

  // Pure virtual function that outputs the player's name to console.
  void displayName();

protected:
  // The piece that this player uses.
  HexBoardPiece piece;

  string playerType;

  // Tracks the nodes on one side of the board that the player has pieces at.
  vector<int> begPos;

  // Tracks the nodes on the other side of the board that the player has pieces at.
  vector<int> endPos;

  // Keeps a record of the positions that this player has played as
  // part of a forest (set of trees). This makes it easy to keep track
  // of connected components. Adapted from Kruskal's algorithm.
  DisjointSet<int> moves;

  // Make a move on the board.
  // @param board A reference to the board being played on.
  // @param position The alphanumeric position on the board to play the piece.
  // @return One of the 3 possible move results.
  HexMoveResult move(HexBoard &board, const string &position);
  // @param boardIndex The zero-based cell index on the board to play the piece.
  HexMoveResult move(HexBoard &board, const int boardIndex);

  HexMoveResult updateMove(HexBoard &board, const int boardIndex);

  // Pure virtual function that records the positions of the player's
  // pieces at the corresponding source/target board edges.
  // @param boardSize The number of hexes on one side of the board.
  // @param boardIndex A valid cell index on the board.
  void updateBoardEdgePos(const int boardSize, const int boardIndex);

  // Checks to see if this player has won the game.
  // @param board A reference to the board being played on.
  // @return True if this player has won, otherwise false.
  bool checkWin();

};


class HexPlayerHuman : public HexPlayer
{
public:
  HexPlayerHuman(bool isFirstPlayer);

  ~HexPlayerHuman();

  virtual bool makeMove(HexBoard &board, const int turnNum);

};


class HexPlayerAI : public HexPlayer
{
public:
  HexPlayerAI(bool isFirstPlayer);

  ~HexPlayerAI();

  virtual bool makeMove(HexBoard &board, const int turnNum);

};

#endif // _HW5_HEX_PLAYER_H_

