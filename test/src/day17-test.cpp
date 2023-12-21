#include <gtest/gtest.h>

#include "aoc/solutions/day17.hpp"

#include <string>

TEST(day17, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day17::part1(base + "day17/sample1.txt"), 102);
  ASSERT_EQ(aoc::day17::part1(base + "day17/input.txt"), 866);
}

TEST(day17, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day17::part2(base + "day17/sample1.txt"), 94);
  ASSERT_EQ(aoc::day17::part2(base + "day17/sample2.txt"), 71);
  ASSERT_EQ(aoc::day17::part2(base + "day17/input.txt"), 1010);
}