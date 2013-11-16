// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexPlayer.hpp

#ifndef _HW4_HEX_PLAYER_H_
#define _HW4_HEX_PLAYER_H_

#include <iostream>
#include <vector>

#include "HexBoard.hpp"
#include "DisjointSet.hpp"

using namespace std;

// Only 3 possible move results.
enum class HexMoveResult : char { VALID, OUTOFBOUNDS, OCCUPIED };

class HexPlayer
{
public:
  // Default constructor.
  HexPlayer();

  // Constructor that initializes the piece this player uses.
  // @param piece The piece that this player will use.
  HexPlayer(const HexBoardPiece piece);

  // Sets the piece that this player will use.
  // @param piece The piece that this player will use.
  void use(const HexBoardPiece piece);

  // Make a move on the board.
  // @param board A reference to the board being played on.
  // @param position The alphanumeric position on the board to play the piece.
  // @return One of the 3 possible move results.
  HexMoveResult move(HexBoard &board, const string &position);

  // Checks to see if this player has won the game.
  // @param board A reference to the board being played on.
  // @return True if this player has won, otherwise false.
  bool checkWin(HexBoard &board);

  // Pure virtual function that outputs the player's name to console.
  virtual void displayName() = 0;

protected:
  // Tracks the nodes on one side of the board that the player has pieces at.
  vector<int> begPos;

  // Tracks the nodes on the other side of the board that the player has pieces at.
  vector<int> endPos;

private:
  // The piece that this player uses.
  HexBoardPiece piece;

  // Keeps a record of the positions that this player has played as
  // part of a forest (set of trees). This makes it easy to keep track
  // of connected components. Adapted from Kruskal's algorithm.
  DisjointSet<int> moves;

  // Pure virtual function that records the positions of the player's
  // pieces at the corresponding source/target board edges.
  // @param boardSize The number of hexes on one side of the board.
  // @param boardIndex A valid cell index on the board.
  virtual void updateBoardEdgePos(int boardSize, int boardIndex) = 0;

};


// This player wins by connecting the east-west sides of the board.
class HexPlayerEastWest : public HexPlayer
{
public:
  // Constructors; calls the base class constructors.
  HexPlayerEastWest() : HexPlayer() {}
  HexPlayerEastWest(const HexBoardPiece piece) : HexPlayer(piece) {}

  // Function that outputs the player's name to console.
  virtual void displayName();

private:
  // Updates the player's pieces at the east-west edges of the board.
  // @param boardSize The number of hexes on one side of the board.
  // @param boardIndex A valid cell index on the board.
  virtual void updateBoardEdgePos(const int boardSize, const int boardIndex);

};


// This player wins by connecting the north-south sides of the board.
class HexPlayerNorthSouth : public HexPlayer
{
public:
  // Constructors; calls the base class constructors.
  HexPlayerNorthSouth() : HexPlayer() {}
  HexPlayerNorthSouth(const HexBoardPiece piece) : HexPlayer(piece) {}

  // Dunction that outputs the player's name to console.
  virtual void displayName();

private:
  // Updates the player's pieces at the north-south edges of the board.
  // @param boardSize The number of hexes on one side of the board.
  // @param boardIndex A valid cell index on the board.
  virtual void updateBoardEdgePos(const int boardSize, const int boardIndex);

};

#endif // _HW4_HEX_PLAYER_H_

