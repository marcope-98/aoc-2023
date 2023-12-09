#include <gtest/gtest.h>

#include "aoc/solutions/day09.hpp"

#include <string>

TEST(day09, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day09::part1(base + "day09/sample.txt"), 114);
  ASSERT_EQ(aoc::day09::part1(base + "day09/input.txt"), 1762065988);
}

TEST(day09, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day09::part2(base + "day09/sample.txt"), 2);
  ASSERT_EQ(aoc::day09::part2(base + "day09/input.txt"), 1066);
}