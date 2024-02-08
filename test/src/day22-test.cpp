#include <gtest/gtest.h>

#include "aoc/solutions/day22.hpp"

#include <string>

TEST(day22, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day22::part1(base + "day22/sample.txt"), 5);
  ASSERT_EQ(aoc::day22::part1(base + "day22/input.txt"), 439);
}

TEST(day22, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day22::part2(base + "day22/sample.txt"), 7);
  ASSERT_EQ(aoc::day22::part2(base + "day22/input.txt"), 43056);
}