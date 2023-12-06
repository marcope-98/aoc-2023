#include <gtest/gtest.h>

#include "aoc/solutions/day06.hpp"

#include <string>

TEST(day06, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day06::part1(base + "day06/sample.txt"), 288);
  ASSERT_EQ(aoc::day06::part1(base + "day06/input.txt"), 449550);
}

TEST(day06, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day06::part2(base + "day06/sample.txt"), 71503);
  ASSERT_EQ(aoc::day06::part2(base + "day06/input.txt"), 28360140);
}