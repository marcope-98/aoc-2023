#include <gtest/gtest.h>

#include "aoc/solutions/day10.hpp"

#include <string>

TEST(day10, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day10::part1(base + "day10/sample1.txt"), 4);
  ASSERT_EQ(aoc::day10::part1(base + "day10/sample2.txt"), 8);
  ASSERT_EQ(aoc::day10::part1(base + "day10/input.txt"), 6701);
}

TEST(day10, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day10::part2(base + "day10/sample3.txt"), 4);
  ASSERT_EQ(aoc::day10::part2(base + "day10/sample4.txt"), 4);
  ASSERT_EQ(aoc::day10::part2(base + "day10/sample5.txt"), 8);
  ASSERT_EQ(aoc::day10::part2(base + "day10/sample6.txt"), 10);
  ASSERT_EQ(aoc::day10::part2(base + "day10/input.txt"), 303);
}