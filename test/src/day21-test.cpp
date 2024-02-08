#include <gtest/gtest.h>

#include "aoc/solutions/day21.hpp"

#include <string>

TEST(day21, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day21::part1(base + "day21/sample.txt", 6), 16);
  ASSERT_EQ(aoc::day21::part1(base + "day21/input.txt", 64), 3699);
}

TEST(day21, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day21::part2(base + "day21/sample.txt", 6), 16);
  ASSERT_EQ(aoc::day21::part2(base + "day21/sample.txt", 10), 50);
  ASSERT_EQ(aoc::day21::part2(base + "day21/sample.txt", 50), 1594);
  ASSERT_EQ(aoc::day21::part2(base + "day21/sample.txt", 100), 6536);
  ASSERT_EQ(aoc::day21::part2(base + "day21/sample.txt", 500), 167004);
  ASSERT_EQ(aoc::day21::part2(base + "day21/sample.txt", 1000), 668697);
  ASSERT_EQ(aoc::day21::part2(base + "day21/sample.txt", 5000), 16733044);
  ASSERT_EQ(aoc::day21::part2(base + "day21/input.txt", 26501365), 613391294577878);
}