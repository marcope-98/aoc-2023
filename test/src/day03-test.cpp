#include <gtest/gtest.h>

#include "aoc/solutions/day03.hpp"

#include <string>

TEST(day03, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day03::part1(base + "/day03/sample.txt"), 4361);
  ASSERT_EQ(aoc::day03::part1(base + "/day03/input.txt"), 525181);
}

TEST(day03, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day03::part2(base + "/day03/sample.txt"), 467835);
  ASSERT_EQ(aoc::day03::part2(base + "/day03/input.txt"), 84289137);
}