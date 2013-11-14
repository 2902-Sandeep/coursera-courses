// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexPlayer.cpp

#include "HexPlayer.hpp"

HexPlayer::HexPlayer()
{

}

HexPlayer::HexPlayer(const HexBoardPiece piece)
{
  use(piece);
}

void HexPlayer::use(const HexBoardPiece piece)
{
  this->piece = piece == HexBoardPiece::X ? HexBoardState::X : HexBoardState::O;
}

HexMoveResult HexPlayer::move(HexBoard &board, const string &position)
{
  int boardIndex = board.check(position);

  if (boardIndex == -1) // invalid position
    return HexMoveResult::OUTOFBOUNDS;
  else if (board.get(boardIndex) != HexBoardState::NONE) // position already occupied
    return HexMoveResult::OCCUPIED;

  board.set(piece, boardIndex);
  return HexMoveResult::VALID;
}

