#include <gtest/gtest.h>

#include "aoc/solutions/day12.hpp"

#include <string>

TEST(day12, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day12::part1(base + "day12/sample.txt"), 21);
  ASSERT_EQ(aoc::day12::part1(base + "day12/input.txt"), 6981);
}

TEST(day12, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day12::part2(base + "day12/sample.txt"), 525152);
  ASSERT_EQ(aoc::day12::part2(base + "day12/input.txt"), 4546215031609);
}