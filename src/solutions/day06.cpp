#include "aoc/solutions/day06.hpp"

#include <iostream>
#include <vector>

#include "aoc/utils/Range.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  std::size_t isqrt(std::size_t x)
  {
    std::size_t m, y, b;
    m = 0x4000000000000000;
    y = 0;
    while (m != 0)
    {
      b = y | m;
      y >>= 1;
      if (x >= b)
      {
        x -= b;
        y |= m;
      }
      m >>= 2;
    }
    return y;
  }

  std::size_t test(const std::size_t &t, const std::size_t &tp) { return tp * (t - tp); }

  aoc::Range *solve(const std::size_t &a, const std::size_t &b, const std::size_t &c)
  {
    const std::size_t b2  = b * b;
    const std::size_t ac4 = 4 * a * c;
    if (b2 < ac4) return nullptr;
    const std::size_t det = isqrt(b2 - ac4);
    aoc::Range *      res = new aoc::Range();
    res->begin()          = ((b - det + 2 * a - 1) / (2 * a)); // ceil
    res->end()            = (b + det) / (2 * a);               // floor

    if (test(b, res->begin()) == c) res->begin()++;
    if (test(b, res->end()) == c) res->end()--;

    return res;
  }

  std::size_t get_solutions(const std::size_t &t, const std::size_t &record)
  {
    aoc::Range *temp = solve(1, t, record);
    if (temp == nullptr) return 0;

    std::size_t result = temp->end() - temp->begin() + 1;
    delete temp;

    return result;
  }

  std::vector<std::size_t> get_input(const std::string &input)
  {
    std::vector<std::size_t> out;
    aoc::vstring             temp = aoc::parse::split_by_delimiters(input, " ");
    for (std::size_t i = 1; i < temp.size(); ++i)
      out.emplace_back(std::stoull(temp[i]));
    return out;
  }

  std::size_t get_concatenated_input(const std::string &input)
  {
    std::string  out;
    aoc::vstring temp = aoc::parse::split_by_delimiters(input, " ");
    for (std::size_t i = 1; i < temp.size(); ++i)
      out += temp[i];
    return std::stoull(out);
  }
} // namespace

std::size_t aoc::day06::part1(const std::string &filename)
{
  aoc::vstring             input    = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t              result   = 1;
  std::vector<std::size_t> time     = get_input(input[0]);
  std::vector<std::size_t> distance = get_input(input[1]);

  for (std::size_t i = 0; i < time.size(); ++i)
    result *= get_solutions(time[i], distance[i]);

  return result;
}

std::size_t aoc::day06::part2(const std::string &filename)
{
  aoc::vstring input    = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  time     = get_concatenated_input(input[0]);
  std::size_t  distance = get_concatenated_input(input[1]);

  return get_solutions(time, distance);
}