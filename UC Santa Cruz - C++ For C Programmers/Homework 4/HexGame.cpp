// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexGame.cpp

#include "HexGame.hpp"

HexGame::HexGame()
{

}

bool HexGame::init()
{
  string inputString;

  printBreak();
  cout << "Hello there! Let's play a game of Hex..." << endl;

  printBreak();
  cout << "How large do you want the board?" << endl
       << "Please enter the number of hexes on one side (between 2 to 26): ";
  getline(cin, inputString);
  int size;
  stringstream(inputString) >> size;
  if ((size < 2) || (size > 26)) {
    size = 11;
    cout << "Uhh, right smart-ass. I'll just pick 11 then..." << endl;
  }

  printBreak();
  cout << "Alright! Creating the " << size << "x" << size << " board..." << endl;
  board.init(size);
  player1.use(HexBoardPiece::X);
  player2.use(HexBoardPiece::O);

  printBreak();
  cout << "Here's a legend for your reference." << endl
       << "I'm still too dumb, so for now I'll let you humans play..." << endl << endl
       << "********************************************************************************" << endl
       << "* STATE          * SYMBOL * NOTES                                              *" << endl
       << "********************************************************************************" << endl
       << "* Empty Location *   .    * self-explanatory                                   *" << endl
       << "* Player 1 Piece *   x    * connects the left to the right side, moves 1st     *" << endl
       << "* Player 2 Piece *   o    * connects the top to the bottom of the board        *" << endl
       << "********************************************************************************" << endl;

  printBreak();
  cout << "Are you ready? (Y to start, N to quit): ";
  getline(cin, inputString);
  bool result = false;
  if (regex_match(inputString, regex("^[Yy]$"))) {
    cout << "Great! Let's begin..." << endl;
    result = true;
  }
  else if (regex_match(inputString, regex("^[Nn]$")))
    cout << "That's too bad...goodbye!" << endl;
  else
    cout << "Really?! Whatever, just start over then..." << endl;

  printBreak();
  return result;
}

void HexGame::start()
{
  cout << "BOARD (no moves)" << endl << endl;
  board.draw();
  cout << endl;
  printBreak();

  int turnNum = 0;
  int currIdx = 1;
  bool isFinished = false;

  while (!isFinished) {
    turnNum++;
    currIdx = (currIdx + 1) % 2;
    move(currIdx, turnNum);
    isFinished = checkWin(currIdx);
  }

  cout << "Congratulations Player " << currIdx + 1 << "! You've won this match!" << endl
       << "Sorry Player " << ((currIdx + 1) % 2) + 1 << ". Try again next time..." << endl
       << "GAME OVER." << endl;
  printBreak();
}

void HexGame::printBreak()
{
  cout << "--------------------------------------------------------------------------------" << endl;
}

void HexGame::move(const int playerIdx, const int turnNum)
{
  bool isValidMove = false;
  string inputLocation;
  HexPlayer *player;

  cout << "Move " << turnNum;
  if (playerIdx == 0) {
    player = &player1;
    cout << ": Player 1 (x)" << endl;
  }
  else {
    player = &player2;
    cout << ": Player 2 (o)" << endl;
  }

  while (!isValidMove) {
    cout << "Please enter a location: ";
    getline(cin, inputLocation);
    switch (player->move(board, inputLocation)) {
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

  printBreak();
  cout << "BOARD (after Move " << turnNum << ")" << endl << endl;
  board.draw();
  cout << endl;
  printBreak();
}

bool HexGame::checkWin(const int playerIdx)
{
  if (playerIdx == 0)
    return player1.checkWin(board);
  else
    return player2.checkWin(board);
}

