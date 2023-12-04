#include <gtest/gtest.h>

#include "aoc/solutions/day04.hpp"

#include <string>

TEST(day04, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day04::part1(base + "day04/sample.txt"), 13);
  ASSERT_EQ(aoc::day04::part1(base + "day04/input.txt"), 21158);
}

TEST(day04, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day04::part2(base + "day04/sample.txt"), 30);
  ASSERT_EQ(aoc::day04::part2(base + "day04/input.txt"), 6050769);
}