#include <gtest/gtest.h>

#include "aoc/solutions/day01.hpp"

#include <string>

TEST(day01, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day01::part1(base + "/day01/sample1.txt"), 142);
  ASSERT_EQ(aoc::day01::part1(base + "/day01/input.txt"), 55123);
}

TEST(day01, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day01::part2(base + "/day01/sample2.txt"), 281);
  ASSERT_EQ(aoc::day01::part2(base + "/day01/input.txt"), 55260);
}