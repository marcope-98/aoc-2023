#include <gtest/gtest.h>

#include "aoc/solutions/day07.hpp"

#include <string>

TEST(day07, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day07::part1(base + "day07/sample.txt"), 6440);
  ASSERT_EQ(aoc::day07::part1(base + "day07/input.txt"), 249748283);
}

TEST(day07, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day07::part2(base + "day07/sample.txt"), 5905);
  ASSERT_EQ(aoc::day07::part2(base + "day07/input.txt"), 248029057);
}