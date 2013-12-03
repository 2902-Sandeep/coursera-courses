// UC Santa Cruz C++ For C Programmers
// Homework 5: Implement Monte Carlo Hex Move Evaluation
// TH Hee
// HexGame.hpp

#ifndef _HW5_HEX_GAME_H_
#define _HW5_HEX_GAME_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <chrono>
#include <random>

#include "HexBoard.hpp"
#include "HexPlayer.hpp"
#include "DisjointSet.hpp"

using namespace std;

class HexGame
{
public:
  // Default constructor.
  HexGame();

  // Default destructor.
  ~HexGame();

  // Requests user input, initializes the game and runs the main game loop.
  void start();

private:
  // The playing board.
  HexBoard *board;

  // The first player (connects east-west). Uses x.
  HexPlayer *player1;
  //HexPlayerEastWest player1;

  // The second player (connects north-south). Uses o.
  HexPlayer *player2;
  //HexPlayerNorthSouth player2;

  bool isPlayWithAI;
  bool isAIMoveFirst;

  // Internal function that outputs a separator to the console (80 dashes).
  void printBreak();

  // Internal function to initialize the hex baord. Prompts for user input.
  void initBoard();

  // Internal function to initialize the players. Prompts for user input.
  void initPlayers();

  // Internal function to start the game. Prompts for user input.
  // @return True to start the game, otherwise false to quit.
  bool checkStartGame();

  void startHumanVsHuman();

  void startHumanVsAI();

  // Internal function that handles and outputs a player's move each turn.
  // @param player The current player.
  // @param turnNum The current move number.
  // @return True if the player's move resulted in a win, otherwise false.
  bool moveHuman(HexPlayer *player, const int turnNum);

  bool moveAI(HexPlayer *player, const int turnNum);

  int evaluatePosition(HexPlayer *player, HexBoard &tempBoard, vector<int> &tempIndices, const int boardIndex);

/*
  void updateDisjointSet(DisjointSet<int> &moves, vector<int> &begPos, vector<int> &endPos);
  void updateDisjointSet(DisjointSet<int> &moves, HexBoard &tempBoard, vector<int> &begPos, vector<int> &endPos);
*/
  bool isNumber(const string &s);

};

// Inline function definitions placed here to avoid linker errors.

inline bool HexGame::isNumber(const string &s)
{
  return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

#endif // _HW5_HEX_GAME_H_

