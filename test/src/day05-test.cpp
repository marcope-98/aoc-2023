#include <gtest/gtest.h>

#include "aoc/solutions/day05.hpp"

#include <string>

TEST(day05, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day05::part1(base + "day05/sample.txt"), 35);
  ASSERT_EQ(aoc::day05::part1(base + "day05/input.txt"), 3374647);
}

TEST(day05, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day05::part2(base + "day05/sample.txt"), 46);
  ASSERT_EQ(aoc::day05::part2(base + "day05/input.txt"), 6082852);
}