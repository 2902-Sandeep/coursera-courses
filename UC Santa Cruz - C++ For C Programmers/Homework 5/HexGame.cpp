// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexGame.cpp

#include "HexGame.hpp"

HexGame::HexGame()
  : board(NULL),
    player1(NULL),
    player2(NULL)
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
  
  if (checkStartGame())
    runGame();
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
    if (isNumber(inputString) && stoi(inputString) == 1) { // two human players
      isValidEntry = true;
      player1 = new HexPlayerHuman(true);
      player2 = new HexPlayerHuman(false);
    }
    else if (isNumber(inputString) && stoi(inputString) == 2) { // play against AI
      isValidEntry = true;
      while (true) { // move order initialization (with AI only)
        cout << "Do you want to go first? (Y/y or N/n): ";
        getline(cin, inputString);
        if (inputString.size() == 1 && (inputString[0] == 'Y' || inputString[0] == 'y')) {
          player1 = new HexPlayerHuman(true);
          player2 = new HexPlayerAI(false);
          break;
        }
        else if (inputString.size() == 1 && (inputString[0] == 'N' || inputString[0] == 'n')) {
          player1 = new HexPlayerAI(true);
          player2 = new HexPlayerHuman(false);
          break;
        }
        else
          cout << "Uhm, that wasn't a response I'm expecting..." << endl;
      }
    }
    else
      cout << "Sorry, that is an invalid selection..." << endl;
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

void HexGame::runGame()
{
  cout << "BOARD (no moves)" << endl << endl;
  board->draw();
  cout << endl;
  printBreak();

  int turnNum = 0;
  bool isFinished = false; // determines if the game is over
  bool toggle = false; // alternates between the players

  // main game loop, runs until a player has won
  while (!isFinished) {
    turnNum++;
    toggle = !toggle;

    cout << "Move " << turnNum << ": ";
    isFinished = toggle ? player1->makeMove(*board, turnNum) : player2->makeMove(*board, turnNum);

    // display the result of the player's move
    printBreak();
    cout << "BOARD (after Move " << turnNum << ")" << endl << endl;
    board->draw();
    cout << endl;
    printBreak();
  }
//    if (toggle)
//      isFinished = isAIMoveFirst ? moveAI(player1, turnNum) : moveHuman(player1, turnNum);
//    else
//      isFinished = isAIMoveFirst ? moveHuman(player2, turnNum) : moveAI(player2, turnNum);
//  }

  // game over message
  cout << "Congratulations ";
  toggle ? player1->displayName() : player2->displayName();
  cout << "! You've won this match!" << endl
       << "Sorry ";
  toggle ? player2->displayName() : player1->displayName();
  cout << ". Try again next time..." << endl
       << "GAME OVER." << endl;
  printBreak();
//  if ((toggle && isAIMoveFirst) || (!toggle && !isAIMoveFirst))
//    cout << "Sorry Human, but you need more practice..." << endl;
//  else
//    cout << "Arrgh! You win this time, Human..." << endl;
//  cout << "GAME OVER." << endl;
//  printBreak();
}

