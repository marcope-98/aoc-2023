#include <gtest/gtest.h>

#include "aoc/solutions/day19.hpp"

#include <string>

TEST(day19, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day19::part1(base + "day19/sample.txt"), 19114);
  ASSERT_EQ(aoc::day19::part1(base + "day19/input.txt"), 399284);
}

TEST(day19, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day19::part2(base + "day19/sample.txt"), 167409079868000);
  ASSERT_EQ(aoc::day19::part2(base + "day19/input.txt"), 121964982771486);
}