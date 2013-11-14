// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexPlayer.hpp

#ifndef _HW4_HEX_PLAYER_H_
#define _HW4_HEX_PLAYER_H_

#include "HexBoard.hpp"

using namespace std;

// Only 2 possible piece types.
enum class HexBoardPiece : char { X, O };

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

private:
  // The piece that this player uses.
  HexBoardState piece;

};

#endif // _HW4_HEX_PLAYER_H_

