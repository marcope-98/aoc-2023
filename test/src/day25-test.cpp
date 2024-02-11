#include <gtest/gtest.h>

#include "aoc/solutions/day25.hpp"

#include <string>

TEST(day25, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day25::part1(base + "day25/sample.txt"), 54);
  ASSERT_EQ(aoc::day25::part1(base + "day25/input.txt"), 583632);
}
