// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexGame.hpp

#ifndef _HW5_HEX_GAME_H_
#define _HW5_HEX_GAME_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "HexBoard.hpp"
#include "HexPlayer.hpp"

using namespace std;

class HexGame
{
public:
  // Default constructor.
  HexGame();

  // Destructor.
  ~HexGame();

  // Requests user input, initializes the game and runs the main game loop.
  void start();

private:
  // The playing board.
  HexBoard *board;

  // The first player (always connects east-west). Uses x.
  HexPlayer *player1;

  // The second player (always connects north-south). Uses o.
  HexPlayer *player2;

  // Internal function that outputs a separator to the console (80 dashes).
  void printBreak();

  // Internal function to initialize the hex baord. Prompts for user input.
  void initBoard();

  // Internal function to initialize the players. Prompts for user input.
  void initPlayers();

  // Internal function to start the game. Prompts for user input.
  // @return True to start the game, otherwise false to quit.
  bool checkStartGame();

  // Internal function that runs the main game loop.
  void runGame();

  // Determines if the given string is a non-empty positive integral number.
  // @param s The string to check.
  // @return True if the string represents a number, otherwise false.
  bool isNumber(const string &s);

};

// Inline function definitions placed here to avoid linker errors.

inline bool HexGame::isNumber(const string &s)
{
  return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

#endif // _HW5_HEX_GAME_H_

