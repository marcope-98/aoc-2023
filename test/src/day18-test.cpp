#include <gtest/gtest.h>

#include "aoc/solutions/day18.hpp"

#include <string>

TEST(day18, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day18::part1(base + "day18/sample.txt"), 62);
  ASSERT_EQ(aoc::day18::part1(base + "day18/input.txt"), 31171);
}

TEST(day18, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day18::part2(base + "day18/sample.txt"), 952408144115);
  ASSERT_EQ(aoc::day18::part2(base + "day18/input.txt"), 131431655002266);
}