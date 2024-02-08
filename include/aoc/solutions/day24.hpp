#ifndef AOC_SOLUTIONS_DAY24_HPP_
#define AOC_SOLUTIONS_DAY24_HPP_

#include <cstdint>
#include <string>

namespace aoc
{
  struct day24
  {
    static std::size_t part1(const std::string &filename, const double &min, const double &max);
    static std::size_t part2(const std::string &filename);
  };
} // namespace aoc

#endif // AOC_SOLUTIONS_DAY24_HPP_