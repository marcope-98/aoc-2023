#include <gtest/gtest.h>

#include "aoc/solutions/day08.hpp"

#include <string>

TEST(day08, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day08::part1(base + "day08/sample1.txt"), 2);
  ASSERT_EQ(aoc::day08::part1(base + "day08/sample2.txt"), 6);
  ASSERT_EQ(aoc::day08::part1(base + "day08/input.txt"), 15517);
}

TEST(day08, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day08::part2(base + "day08/sample3.txt"), 6);
  ASSERT_EQ(aoc::day08::part2(base + "day08/input.txt"), 14935034899483);
}
