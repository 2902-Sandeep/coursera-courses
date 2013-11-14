// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// HexGame.hpp

#ifndef _HW4_HEX_GAME_H_
#define _HW4_HEX_GAME_H_

#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "HexBoard.hpp"
#include "HexPlayer.hpp"

using namespace std;

class HexGame
{
public:
  // Default constructor.
  HexGame();

  // Requests user input and initializes the game.
  // @return True if we are ready to start the game, otherwise false.
  bool init();

  // The main game loop runs in here.
  void start();

private:
  // The playing board.
  HexBoard board;

  // The first human player.
  HexPlayer player1;

  // The second human player.
  HexPlayer player2;

  // Internal function that outputs a separator to the console (80 dashes).
  void printBreak();

};

#endif // _HW4_HEX_GAME_H_

