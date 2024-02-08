#include <gtest/gtest.h>

#include "aoc/solutions/day23.hpp"

#include <string>

TEST(day23, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day23::part1(base + "day23/sample.txt"), 94);
  ASSERT_EQ(aoc::day23::part1(base + "day23/input.txt"), 2114);
}

TEST(day23, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day23::part2(base + "day23/sample.txt"), 154);
  ASSERT_EQ(aoc::day23::part2(base + "day23/input.txt"), 6322);
}