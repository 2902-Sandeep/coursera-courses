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
  board.set(piece, boardIndex);
  moves.add(boardIndex);

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

bool HexPlayerHuman::makeMove(HexBoard &board)
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

bool HexPlayerAI::makeMove(HexBoard &board)
{
  displayName(); cout << endl; // player selection

//  bool isValidMove = false;
//  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on current time
//  default_random_engine generator(seed); // seed the random number engine
//  uniform_int_distribution<int> distribution(0, board.getNumCells() - 1); // initialize uniform distribution

  vector<int> openIndices;
  board.getUnoccupiedCellIndices(openIndices);

  int numWins = 0, curWins = 0, selectedIndex = 0;
  for (auto &idx : openIndices) {
    curWins = evaluatePosition(idx, board, openIndices);
    if (numWins < curWins) {
      numWins = curWins;
      selectedIndex = idx;
    }
  }

  // make the selected move
  move(board, selectedIndex);

  // check to see if it was a winning move
  return checkWin();
}

int HexPlayerAI::evaluatePosition(const int curIdx, HexBoard &board, vector<int> &openIndices)
{
  // remove the index currently being evaluated
  vector<int> tempIndices = openIndices;
  tempIndices.erase(find(tempIndices.begin(), tempIndices.end(), curIdx));

  // determine the pieces being used
  HexBoardPiece opponentPiece = piece == HexBoardPiece::X ? HexBoardPiece::O : HexBoardPiece::X;
  board.set(piece, curIdx); // fix the piece currently being evaluated

  // get the indices of all cells currently occupied by the player
  vector<int> playerIndices;
  piece == HexBoardPiece::X ? board.getXCellIndices(playerIndices) : board.getOCellIndices(playerIndices);

  int numWins = 0, iter = 0;
  while (iter++ < 1000) {
    //DisjointSet<int> playerMoves;
    //HexBoard tempBoard = board;
    //for (int &i : playerIndices)
    //  updateDisjointSet(playerMoves, i, tempBoard);

    // shuffle the indices; this will be the random order of moves
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on current time
    shuffle(tempIndices.begin(), tempIndices.end(), default_random_engine(seed));

    for (int i = 0; i < tempIndices.size(); ++i) {
      if (i % 2 == 0)
        board.set(opponentPiece, tempIndices[i]);
        //tempBoard.set(opponentPiece, tempIndices[i]);
      else {
        board.set(piece, tempIndices[i]);
        //tempBoard.set(piece, tempIndices[i]);
        //updateDisjointSet(playerMoves, tempIndices[i], tempBoard);
      }
    }

    if (true) ++numWins;
    //if (tempPlayer->checkWin(tempBoard)) ++numWins;
  }

  // restore board
  //board.set(HexBoardPiece::NONE, curIdx);
  for (int &idx : openIndices)
    board.set(HexBoardPiece::NONE, idx);

  return numWins;
}

void HexPlayerAI::updateDisjointSet(DisjointSet<int> &playerMoves, const int boardIndex, HexBoard &board)
{
  playerMoves.add(boardIndex);

  vector<int> neighbors;
  board.getNeighbors(boardIndex, neighbors);
  for (auto &i : neighbors) {
    if (board.get(i) == piece) // the neighboring piece belongs to this player
      playerMoves.merge(i, boardIndex); // merge the connected components
  }
}

