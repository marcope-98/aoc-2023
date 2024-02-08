#include <gtest/gtest.h>

#include "aoc/solutions/day20.hpp"

#include <string>

TEST(day20, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day20::part1(base + "day20/sample1.txt"), 32000000);
  ASSERT_EQ(aoc::day20::part1(base + "day20/sample2.txt"), 11687500);
  ASSERT_EQ(aoc::day20::part1(base + "day20/input.txt"), 912199500);
}
TEST(day20, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day20::part2(base + "day20/input.txt"), 237878264003759);
}