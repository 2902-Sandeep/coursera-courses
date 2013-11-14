// Testing framework for the HexBoard class.

#include <iostream>
#include <string>

#include "HexBoard.hpp"
#include "CustomAssert.hpp"

void HexBoard_TestInitialization(int size)
{
  HexBoard test(size);

  size = size < 2 ? 2 : size;
  size = size > 26 ? 26 : size;

  int count = 0;
  string alpha, num;
  for (int i = 1; i <= size; ++i) {
    num = std::to_string(i);
    for (int j = 65; j < 65 + size; ++j) {
      alpha = static_cast<char>(j);
      ASSERT_CONDITION(test.check(alpha + num) == count, "Alpha-numeric check");
      ASSERT_CONDITION(test.check(num + alpha) == count, "Numeric-alpha check");
      count++;
    }
  }

  ASSERT_CONDITION(test.check("123Z") == -1, "Invalid check, out of range");
  ASSERT_CONDITION(test.check("y123") == -1, "Invalid check, out of range");
  ASSERT_CONDITION(test.check("09H8") == -1, "Invalid check");
  ASSERT_CONDITION(test.check("R17f") == -1, "Invalid check");
  ASSERT_CONDITION(test.check("Q4!?") == -1, "Invalid check");
  ASSERT_CONDITION(test.check("5p ?") == -1, "Invalid check");
}

void HexBoard_TestDraw()
{
  std::cerr << "Running Test for Hex Board drawing..." << std::endl;

  HexBoard testSmall(9);
  testSmall.draw();

  HexBoard testLarge(26);
  testLarge.set(HexBoardState::X, testLarge.check("Z23"));
  testLarge.set(HexBoardState::X, testLarge.check("Y24"));
  testLarge.set(HexBoardState::X, testLarge.check("24X"));
  testLarge.set(HexBoardState::X, testLarge.check("23X"));
  testLarge.set(HexBoardState::X, testLarge.check("W23"));
  testLarge.set(HexBoardState::X, testLarge.check("V24"));
  testLarge.set(HexBoardState::X, testLarge.check("V25"));
  testLarge.set(HexBoardState::X, testLarge.check("26U"));
  testLarge.set(HexBoardState::O, testLarge.check("A5"));
  testLarge.set(HexBoardState::O, testLarge.check("B4"));
  testLarge.set(HexBoardState::O, testLarge.check("4C"));
  testLarge.set(HexBoardState::O, testLarge.check("D3"));
  testLarge.set(HexBoardState::O, testLarge.check("3E"));
  testLarge.set(HexBoardState::O, testLarge.check("F2"));
  testLarge.set(HexBoardState::O, testLarge.check("G2"));
  testLarge.set(HexBoardState::O, testLarge.check("1H"));
  testLarge.draw();

  ASSERT_CONDITION(testLarge.get(testLarge.check("N15")) == HexBoardState::NONE, "NONE state check");
  ASSERT_CONDITION(testLarge.get(testLarge.check("X23")) == HexBoardState::X, "X state check");
  ASSERT_CONDITION(testLarge.get(testLarge.check("3D")) == HexBoardState::O, "O state check");

  testLarge.reset();
  testLarge.draw();
}

int main()
{
  std::cerr << "Running Test for Hex Board initialization..." << std::endl;

  for (int i = -1; i < 30; ++i)
    HexBoard_TestInitialization(i);

  HexBoard_TestDraw();

  return 0;
}

