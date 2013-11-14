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
  cout << "How large do you want the board?" << endl;
  cout << "Please enter the number of hexes on one side (between 2 to 26): ";
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
  cout << "Here's a legend for your reference." << endl;
  cout << "I'm still too dumb, so for now I'll let you Humans play..." << endl << endl;
  cout << "********************************************************************************" << endl;
  cout << "* STATE          * SYMBOL * NOTES                                              *" << endl;
  cout << "********************************************************************************" << endl;
  cout << "* Empty Location *   .    * self-explanatory                                   *" << endl;
  cout << "* Player 1 Piece *   x    * connects the left to the right side, moves 1st     *" << endl;
  cout << "* Player 2 Piece *   o    * connects the top to the bottom of the board        *" << endl;
  cout << "********************************************************************************" << endl;

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

}

void HexGame::printBreak()
{
  cout << "--------------------------------------------------------------------------------" << endl;
}

