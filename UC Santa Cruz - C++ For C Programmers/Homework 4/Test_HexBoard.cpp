// Testing framework for the HexBoard class.

#include <iostream>
#include <string>

#include "HexBoard.hpp"
#include "CustomAssert.hpp"

void HexBoard_TestSize(int size)
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

int main()
{
  std::cerr << "Running Test for Hex Board sizes..." << endl;

  for (int i = -1; i < 30; ++i)
    HexBoard_TestSize(i);

  return 0;
}

