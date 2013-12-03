// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexGame.cpp

#include "HexGame.hpp"

HexGame::HexGame()
  : board(NULL),
    player1(NULL),
    player2(NULL),
    isPlayWithAI(false),
    isAIMoveFirst(false)
{

}

HexGame::~HexGame()
{
  if (board) delete board;
  if (player1) delete player1;
  if (player2) delete player2;
}

void HexGame::start()
{
  printBreak();
  cout << "Hello there! Let's play a game of Hex..." << endl;

  initBoard();
  initPlayers();
  
  if (checkStartGame()) {
    cout << "BOARD (no moves)" << endl << endl;
    board->draw();
    cout << endl;
    printBreak();

    isPlayWithAI ? startHumanVsAI() : startHumanVsHuman();
  }
}

void HexGame::printBreak()
{
  cout << "--------------------------------------------------------------------------------" << endl;
}

void HexGame::initBoard()
{
  string inputString;
  bool isValidEntry = false;

  // board size selection
  printBreak();
  cout << "How large do you want the board?" << endl;
  while (!isValidEntry) {
    cout << "Please enter the number of hexes on one side (between 2 to 26): ";
    getline(cin, inputString);
    if (isNumber(inputString) && stoi(inputString) >= 2 && stoi(inputString) <= 26)
      isValidEntry = true;
    else
      cout << "Uhh, that is an invalid number..." << endl;
  }

  // board initialization
  printBreak();
  cout << "Alright! Creating the " << stoi(inputString) << "x" << stoi(inputString) << " board..." << endl;
  board = new HexBoard(stoi(inputString));
}

void HexGame::initPlayers()
{
  string inputString;
  bool isValidEntry = false;

  // player initialization
  printBreak();
  cout << "How do you want to play?" << endl
       << " 1. Human vs. Human" << endl
       << " 2. Human vs. Computer" << endl;
  while (!isValidEntry) {
    cout << "Please select your desired game mode (1 or 2): ";
    getline(cin, inputString);
    if (isNumber(inputString) && stoi(inputString) == 1) {
      isValidEntry = true;
      player1 = new HexPlayerEastWest(true);
      player2 = new HexPlayerNorthSouth(true);
    }
    else if (isNumber(inputString) && stoi(inputString) == 2) {
      isValidEntry = true;
      isPlayWithAI = true;
    }
    else
      cout << "Sorry, that is an invalid selection..." << endl;
  }

  // move order initialization (with AI only)
  if (isPlayWithAI) {
    isValidEntry = false;
    while (!isValidEntry) {
      cout << "Do you want to go first? (Y/y or N/n): ";
      getline(cin, inputString);
      if (inputString.size() == 1 && (inputString[0] == 'Y' || inputString[0] == 'y')) {
        isValidEntry = true;
        isAIMoveFirst = false;
        player1 = new HexPlayerEastWest(true);
        player2 = new HexPlayerNorthSouth(false);
      }
      else if (inputString.size() == 1 && (inputString[0] == 'N' || inputString[0] == 'n')) {
        isValidEntry = true;
        isAIMoveFirst = true;
        player1 = new HexPlayerEastWest(false);
        player2 = new HexPlayerNorthSouth(true);
      }
      else
        cout << "Uhm, that wasn't a response I'm expecting..." << endl;
    }
  }
}

bool HexGame::checkStartGame()
{
  string inputString;
  bool isValidEntry = false, result = false;

  // display legend
  printBreak();
  cout << "Awesome! Here's a legend for your reference:" << endl << endl
       << "********************************************************************************" << endl
       << "* STATE          * SYMBOL * NOTES                                              *" << endl
       << "********************************************************************************" << endl
       << "* Empty Location *   .    * self-explanatory                                   *" << endl
       << "* Player 1 Piece *   x    * connects the left to the right side, moves 1st     *" << endl
       << "* Player 2 Piece *   o    * connects the top to the bottom of the board        *" << endl
       << "********************************************************************************" << endl;

  // prompt to start game or quit
  printBreak();
  while (!isValidEntry) {
    cout << "Are you ready? (Y/y to start, N/n to quit): ";
    getline(cin, inputString);
    if (inputString.size() == 1 && (inputString[0] == 'Y' || inputString[0] == 'y')) {
      isValidEntry = true;
      cout << "Great! Let's begin..." << endl;
      result = true;
    }
    else if (inputString.size() == 1 && (inputString[0] == 'N' || inputString[0] == 'n')) {
      isValidEntry = true;
      cout << "That's too bad...goodbye!" << endl;
    }
    else
      cout << "Uhh, that wasn't a response I was looking for..." << endl;
  }

  printBreak();
  return result;
}

void HexGame::startHumanVsHuman()
{
  int turnNum = 0;
  bool isFinished = false; // determines if the game is over
  bool toggle = false; // alternates between the players

  // main game loop, runs until a player has won
  while (!isFinished) {
    turnNum++;
    toggle = !toggle;
    isFinished = toggle ? moveHuman(player1, turnNum) : moveHuman(player2, turnNum);
  }

  // game over message
  cout << "Congratulations ";
  toggle ? player1->displayName() : player2->displayName();
  cout << "! You've won this match!" << endl
       << "Sorry ";
  toggle ? player2->displayName() : player1->displayName();
  cout << ". Try again next time..." << endl
       << "GAME OVER." << endl;
  printBreak();
}

void HexGame::startHumanVsAI()
{
  int turnNum = 0;
  bool isFinished = false; // determines if the game is over
  bool toggle = false; // alternates between the players

  // main game loop, runs until a player has won
  while (!isFinished) {
    turnNum++;
    toggle = !toggle;
    if (toggle)
      isFinished = isAIMoveFirst ? moveAI(player1, turnNum) : moveHuman(player1, turnNum);
    else
      isFinished = isAIMoveFirst ? moveHuman(player2, turnNum) : moveAI(player2, turnNum);
  }

  // game over message
  if ((toggle && isAIMoveFirst) || (!toggle && !isAIMoveFirst))
    cout << "Sorry Human, but you need more practice..." << endl;
  else
    cout << "Arrgh! You win this time, Human..." << endl;
  cout << "GAME OVER." << endl;
  printBreak();
}

bool HexGame::moveHuman(HexPlayer *player, const int turnNum)
{
  bool isValidMove = false;
  string inputLocation;

  // player selection
  cout << "Move " << turnNum << ": ";
  player->displayName();
  cout << endl;

  // loop that waits for a valid player input
  while (!isValidMove) {
    cout << "Please enter a location: ";
    getline(cin, inputLocation);
    switch (player->move(*board, inputLocation)) {
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

  // display the result of the player's move
  printBreak();
  cout << "BOARD (after Move " << turnNum << ")" << endl << endl;
  board->draw();
  cout << endl;
  printBreak();

  // check to see if it was a winning move
  return player->checkWin(*board);
}

bool HexGame::moveAI(HexPlayer *player, const int turnNum)
{
  bool isValidMove = false;
  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on current time
  default_random_engine generator(seed); // seed the random number engine
  uniform_int_distribution<int> distribution(0, board->getNumCells() - 1); // initialize uniform distribution

  // player selection
  cout << "Move " << turnNum << ": ";
  player->displayName();
  cout << endl;
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
  // display the result of the player's move
  printBreak();
  cout << "BOARD (after Move " << turnNum << ")" << endl << endl;
  board->draw();
  cout << endl;
  printBreak();

  // check to see if it was a winning move
  return player->checkWin(*board);
}

int HexGame::evaluatePosition(HexPlayer *player, HexBoard &tempBoard, vector<int> &tempIndices, const int boardIndex)
{
  // remove the index currently being evaluated
  auto it = find(tempIndices.begin(), tempIndices.end(), boardIndex);
  tempIndices.erase(it);

  // determine the pieces being used
  HexBoardPiece opponentPiece = player->getPiece() == HexBoardPiece::X ? HexBoardPiece::O : HexBoardPiece::X;
  tempBoard.set(player->getPiece(), boardIndex); // fix the piece currently being evaluated

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

    int i = 0;
    for (it = tempIndices.begin(); it != tempIndices.end(); ++it, ++i) {
    /*
      if (i % 2 == 0)
        tempBoard.set(opponentPiece, *it);
      else {
        cout << "moving.." << endl;
        updateDisjointSet(moves, tempBoard, *it, );
        tempBoard.set(player->getPiece(), *it);
      }
      */
      i % 2 == 0 ? tempBoard.set(opponentPiece, *it) : tempBoard.set(player->getPiece(), *it);
    }

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

