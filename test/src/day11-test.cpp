#include <gtest/gtest.h>

#include "aoc/solutions/day11.hpp"

#include <string>

TEST(day11, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day11::part1(base + "day11/sample.txt", 2), 374);
  ASSERT_EQ(aoc::day11::part1(base + "day11/input.txt", 2), 10289334);
}

TEST(day11, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day11::part2(base + "day11/sample.txt", 10), 1030);
  ASSERT_EQ(aoc::day11::part2(base + "day11/sample.txt", 100), 8410);
  ASSERT_EQ(aoc::day11::part2(base + "day11/input.txt", 1000000), 649862989626);
}