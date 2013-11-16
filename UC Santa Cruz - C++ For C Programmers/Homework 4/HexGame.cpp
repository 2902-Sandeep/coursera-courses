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

  // board size selection
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

  // board and player initialization
  printBreak();
  cout << "Alright! Creating the " << size << "x" << size << " board..." << endl;
  board.init(size);
  player1.use(HexBoardPiece::X);
  player2.use(HexBoardPiece::O);

  // display legend
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

  // prompt to start game or quit
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
  bool isFinished = false; // determines if the game is over
  bool toggle = false; // alternates between the players

  // main game loop, runs until a player has won
  while (!isFinished) {
    turnNum++;
    toggle = !toggle;
    isFinished = toggle ? move(&player1, turnNum) : move(&player2, turnNum);
  }

  // game over message
  cout << "Congratulations ";
  toggle ? player1.displayName() : player2.displayName();
  cout << "! You've won this match!" << endl
       << "Sorry ";
  toggle ? player2.displayName() : player1.displayName();
  cout << ". Try again next time..." << endl
       << "GAME OVER." << endl;
  printBreak();
}

void HexGame::printBreak()
{
  cout << "--------------------------------------------------------------------------------" << endl;
}

bool HexGame::move(HexPlayer *player, const int turnNum)
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

  // display the result of the player's move
  printBreak();
  cout << "BOARD (after Move " << turnNum << ")" << endl << endl;
  board.draw();
  cout << endl;
  printBreak();

  // check to see if it was a winning move
  return player->checkWin(board);
}

