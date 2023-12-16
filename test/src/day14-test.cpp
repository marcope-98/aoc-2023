#include <gtest/gtest.h>

#include "aoc/solutions/day14.hpp"

#include <string>

TEST(day14, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day14::part1(base + "day14/sample.txt"), 136);
  ASSERT_EQ(aoc::day14::part1(base + "day14/input.txt"), 108614);
}

TEST(day14, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day14::part2(base + "day14/sample.txt", 1000000000), 64);
  ASSERT_EQ(aoc::day14::part2(base + "day14/input.txt", 1000000000), 96447);
}