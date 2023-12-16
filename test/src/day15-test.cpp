#include <gtest/gtest.h>

#include "aoc/solutions/day15.hpp"

#include <string>

TEST(day15, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day15::part1(base + "day15/sample.txt"), 1320);
  ASSERT_EQ(aoc::day15::part1(base + "day15/input.txt"), 513158);
}

TEST(day15, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day15::part2(base + "day15/sample.txt"), 145);
  ASSERT_EQ(aoc::day15::part2(base + "day15/input.txt"), 200277);
}