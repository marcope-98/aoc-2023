#ifndef AOC_SOLUTIONS_DAY14_HPP_
#define AOC_SOLUTIONS_DAY14_HPP_

#include <cstdint>
#include <string>

namespace aoc
{
  struct day14
  {
    static std::size_t part1(const std::string &filename);
    static std::size_t part2(const std::string &filename, const std::size_t &cycles);
  };
} // namespace aoc

#endif // AOC_SOLUTIONS_DAY14_HPP_