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

bool HexPlayer::move(HexBoard &board, const string &position)
{
  int boardIndex = board.check(position);

  // invalid position, or position already occupied
  if ((boardIndex == -1) || (board.get(boardIndex) != HexBoardState::NONE))
    return false;

  board.set(piece, boardIndex);
  return true;
}

