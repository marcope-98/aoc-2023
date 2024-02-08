#include <gtest/gtest.h>

#include "aoc/solutions/day24.hpp"

#include <string>

TEST(day24, part1)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day24::part1(base + "day24/sample.txt", 7., 27.), 2);
  ASSERT_EQ(aoc::day24::part1(base + "day24/input.txt", 200000000000000., 400000000000000.), 11098);
}

TEST(day24, part2)
{
  std::string base = std::string(TXT_FILE_DIR);
  ASSERT_EQ(aoc::day24::part2(base + "day24/sample.txt"), 47);
  ASSERT_EQ(aoc::day24::part2(base + "day24/input.txt"), 920630818300104);
}
