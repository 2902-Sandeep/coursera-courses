// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexPlayer.cpp

#include "HexPlayer.hpp"

HexPlayer::HexPlayer(bool isFirstPlayer)
{
  // player 1: always connects east-west, uses X
  // player 2: always connects north-south, uses O
  piece = isFirstPlayer ? HexBoardPiece::X : HexBoardPiece::O;
}

HexPlayer::~HexPlayer()
{

}

void HexPlayer::displayName()
{
  if (piece == HexBoardPiece::X)
    cout << playerType << " Player 1 (x)";
  else // piece == HexBoardPiece::O
    cout << playerType << " Player 2 (o)";
}

HexMoveResult HexPlayer::move(HexBoard &board, const string &position)
{
  return updateMove(board, board.check(position));
}

HexMoveResult HexPlayer::move(HexBoard &board, const int boardIndex)
{
  return updateMove(board, board.check(boardIndex));
}

HexMoveResult HexPlayer::updateMove(HexBoard &board, const int boardIndex)
{
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

void HexPlayer::updateBoardEdgePos(const int boardSize, const int boardIndex)
{
  if (piece == HexBoardPiece::X) {
    if (boardIndex % boardSize == 0)
      begPos.push_back(boardIndex); // keep track of the left nodes
    else if (boardIndex % boardSize == boardSize - 1)
      endPos.push_back(boardIndex); // keep track of the right nodes
  }
  else { // piece == HexBoardPiece::O
    if (boardIndex < boardSize)
      begPos.push_back(boardIndex); // keep track of the top nodes
    else if (boardIndex >= boardSize * (boardSize - 1))
      endPos.push_back(boardIndex); // keep track of the bottom nodes
  }
}

bool HexPlayer::checkWin()
{
  // for each pair of starting-ending positions, check if they are connected
  for (int &beg : begPos) {
    for (int &end : endPos) {
      if (moves.isConnected(beg, end))
        return true;
    }
  }

  return false;
}


HexPlayerHuman::HexPlayerHuman(bool isFirstPlayer)
  : HexPlayer(isFirstPlayer)
{
  playerType = "(Human)";
}

HexPlayerHuman::~HexPlayerHuman()
{

}

bool HexPlayerHuman::makeMove(HexBoard &board, const int turnNum)
{
  displayName(); cout << endl; // player selection

  bool isValidMove = false;
  string inputLocation;

  // loop that waits for a valid player input
  while (!isValidMove) {
    cout << "Please enter a location: ";
    getline(cin, inputLocation);
    switch (move(board, inputLocation)) {
    case HexMoveResult::VALID:
      isValidMove = true;
      break;
    case HexMoveResult::OCCUPIED:
      cout << "Whoops! That location is already occupied, try again." << endl;
      break;
    case HexMoveResult::OUTOFBOUNDS:
    default:
      cout << "Whoops! You've entered an invalid location, try again." << endl;
      break;
    }
  }

  // check to see if it was a winning move
  return checkWin();
}


HexPlayerAI::HexPlayerAI(bool isFirstPlayer)
  : HexPlayer(isFirstPlayer)
{
  playerType = "(AI)";
}

HexPlayerAI::~HexPlayerAI()
{

}

bool HexPlayerAI::makeMove(HexBoard &board, const int turnNum)
{
  displayName(); cout << endl; // player selection

  bool isValidMove = false;
  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on current time
  default_random_engine generator(seed); // seed the random number engine
  uniform_int_distribution<int> distribution(0, board.getNumCells() - 1); // initialize uniform distribution

/*
  HexBoard tempBoard = board;
  vector<int> tempIndices = freeBoardIndices;
  int numWins = 0, curWins = 0;
  auto selectedIt = freeBoardIndices.begin();
  for (auto it = freeBoardIndices.begin(); it != freeBoardIndices.end(); ++it) {
    curWins = evaluatePosition(player, board, tempIndices, *it);
    if (numWins < curWins) {
      numWins = curWins;
      selectedIt = it;
    }
  }

  // make the selected move
  player->move(*board, *selectedIt);
*/

  // check to see if it was a winning move
  return checkWin();
}

int HexGame::evaluatePosition(HexPlayer *player, HexBoard &tempBoard, vector<int> &tempIndices, const int boardIndex)
{
  // remove the index currently being evaluated
  auto it = find(tempIndices.begin(), tempIndices.end(), boardIndex);
  tempIndices.erase(it);

  // determine the pieces being used
//  HexBoardPiece opponentPiece = player->getPiece() == HexBoardPiece::X ? HexBoardPiece::O : HexBoardPiece::X;
//  tempBoard.set(player->getPiece(), boardIndex); // fix the piece currently being evaluated

  int numWins = 0;
  int iter = 0;
  while (iter++ < 1000) {
    /*
    DisjointSet<int> moves;
    vector<int> begPos, endPos;
    updateDisjointSet(moves, begPos, endPos);
    */
    // shuffle the indices; this will be the random order of moves
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on current time
    shuffle(tempIndices.begin(), tempIndices.end(), default_random_engine(seed));

//    int i = 0;
//    for (it = tempIndices.begin(); it != tempIndices.end(); ++it, ++i) {
    /*
      if (i % 2 == 0)
        tempBoard.set(opponentPiece, *it);
      else {
        cout << "moving.." << endl;
        updateDisjointSet(moves, tempBoard, *it, );
        tempBoard.set(player->getPiece(), *it);
      }
      */
//      i % 2 == 0 ? tempBoard.set(opponentPiece, *it) : tempBoard.set(player->getPiece(), *it);
//    }

    if (true) ++numWins;
    //if (tempPlayer->checkWin(tempBoard)) ++numWins;
  }

  // restore vector of open positions
  tempIndices.push_back(boardIndex);

  // restore board
  for (it = tempIndices.begin(); it != tempIndices.end(); ++it)
    tempBoard.set(HexBoardPiece::NONE, *it);

  return numWins;
}
/*
void HexGame::updateDisjointSet(DisjointSet<int> &moves, vector<int> &begPos, vector<int> &endPos)
{
  for (auto it = AIBoardIndices.begin(); it != AIBoardIndices.end(); ++it) {
    moves.add(*it);
    if (isAIMoveFirst) {
      if (*it % board.getSize() == 0)
        begPos.push_back(*it);
      else if (*it % board.getSize() == board.getSize() - 1)
        endPos.push_back(*it);
    }
    else {
      if (*it < board.getSize())
        begPos.push_back(*it);
      else if (*it >= board.getSize() * (board.getSize() - 1))
        endPos.push_back(*it);
    }

    vector<int> neighbors;
    board.getNeighbors(*it, neighbors);
    for (auto it2 = neighbors.begin(); it != neighbors.end(); ++it) {
      if (board.get(*it2) == (isAIMoveFirst ? HexBoardPiece::X : HexBoardPiece::O))
        moves.merge(*it2, *it);
    }
  }
}

void HexGame::updateDisjointSet(DisjointSet<int> &moves, HexBoard &tempBoard, vector<int> &begPos, vector<int> &endPos)
{
  for (auto it = AIBoardIndices.begin(); it != AIBoardIndices.end(); ++it) {
    moves.add(*it);
    if (isAIMoveFirst) {
      if (*it % board.getSize() == 0)
        begPos.push_back(*it);
      else if (*it % board.getSize() == board.getSize() - 1)
        endPos.push_back(*it);
    }
    else {
      if (*it < board.getSize())
        begPos.push_back(*it);
      else if (*it >= board.getSize() * (board.getSize() - 1))
        endPos.push_back(*it);
    }

    vector<int> neighbors;
    board.getNeighbors(*it, neighbors);
    for (auto it2 = neighbors.begin(); it != neighbors.end(); ++it) {
      if (board.get(*it2) == (isAIMoveFirst ? HexBoardPiece::X : HexBoardPiece::O))
        moves.merge(*it2, *it);
    }
  }
}
*/

