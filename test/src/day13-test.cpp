#include <gtest/gtest.h>

#include "aoc/solutions/day13.hpp"

#include <string>

TEST(day13, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day13::part1(base + "day13/sample.txt"), 405);
  ASSERT_EQ(aoc::day13::part1(base + "day13/input.txt"), 29213);
}

TEST(day13, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day13::part2(base + "day13/sample.txt"), 400);
  ASSERT_EQ(aoc::day13::part2(base + "day13/input.txt"), 37453);
}