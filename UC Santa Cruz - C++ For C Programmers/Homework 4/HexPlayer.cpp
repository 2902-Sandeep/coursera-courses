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
  this->piece = piece;
}

HexMoveResult HexPlayer::move(HexBoard &board, const string &position)
{
  int boardIndex = board.check(position);

  if (boardIndex == -1) // invalid position
    return HexMoveResult::OUTOFBOUNDS;
  else if (board.get(boardIndex) != HexBoardPiece::NONE) // position already occupied
    return HexMoveResult::OCCUPIED;

  // record this move
  moves.add(boardIndex);
  board.set(piece, boardIndex);

  // record if this is an edge piece (a move at the edge of the board)
  updateBoardEdgePos(board.getSize(), boardIndex);

  // update the connected nodes
  vector<int> neighbors;
  board.getNeighbors(boardIndex, neighbors);
  for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
    if (board.get(*it) == piece) // the neighboring piece belongs to this player
      moves.merge(*it, boardIndex); // merge the connected components
  }

  return HexMoveResult::VALID;
}

bool HexPlayer::checkWin(HexBoard &board)
{
  // for each pair of starting-ending positions, check if they are connected
  for (auto itBeg = begPos.begin(); itBeg != begPos.end(); ++itBeg) {
    for (auto itEnd = endPos.begin(); itEnd != endPos.end(); ++itEnd) {
      if (moves.isConnected(*itBeg, *itEnd))
        return true;
    }
  }

  return false;
}


void HexPlayerEastWest::displayName()
{
  cout << "Player 1 (x)";
}

void HexPlayerEastWest::updateBoardEdgePos(const int boardSize, const int boardIndex)
{
  if (boardIndex % boardSize == 0)
    begPos.push_back(boardIndex); // keep track of the left nodes
  else if (boardIndex % boardSize == boardSize - 1)
    endPos.push_back(boardIndex); // keep track of the right nodes
}


void HexPlayerNorthSouth::displayName()
{
  cout << "Player 2 (o)";
}

void HexPlayerNorthSouth::updateBoardEdgePos(const int boardSize, const int boardIndex)
{
  if (boardIndex < boardSize)
    begPos.push_back(boardIndex); // keep track of the top nodes
  else if (boardIndex >= boardSize * (boardSize - 1))
    endPos.push_back(boardIndex); // keep track of the bottom nodes
}

