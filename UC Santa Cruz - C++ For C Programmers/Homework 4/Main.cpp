// UC Santa Cruz C++ For C Programmers
// Homework 4: Implement Hex Board
// TH Hee
// Main.cpp
// Hex game implementation.

#include "HexGame.hpp"

using namespace std;

int main()
{
  HexGame game;

  if (game.init())
    game.start();

  return 0;
}

