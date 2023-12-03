#include <gtest/gtest.h>

#include "aoc/solutions/day02.hpp"

#include <string>

TEST(day02, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day02::part1(base + "/day02/sample.txt"), 8);
  ASSERT_EQ(aoc::day02::part1(base + "/day02/input.txt"), 2105);
}

TEST(day02, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day02::part2(base + "/day02/sample.txt"), 2286);
  ASSERT_EQ(aoc::day02::part2(base + "/day02/input.txt"), 72422);
}