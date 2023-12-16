#include <gtest/gtest.h>

#include "aoc/solutions/day16.hpp"

#include <string>

TEST(day16, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day16::part1(base + "day16/sample.txt"), 46);
  ASSERT_EQ(aoc::day16::part1(base + "day16/input.txt"), 7884);
}

TEST(day16, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day16::part2(base + "day16/sample.txt"), 51);
  ASSERT_EQ(aoc::day16::part2(base + "day16/input.txt"), 8185);
}