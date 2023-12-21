#include "aoc/solutions/day01.hpp"

// stl
#include <vector>
// aoc/utils
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  std::string hashmap[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  bool        is_digit(const char value) { return value >= '0' && value <= '9'; }
  std::size_t get_digit(const std::string &str) { return std::size_t(str.front() - '0') * 10 + std::size_t(str.back() - '0'); }
  std::string preprocess(const std::string &str)
  {
    std::string res;
    for (std::size_t i = 0; i < str.size(); ++i)
    {
      if (is_digit(str[i]))
        res += str[i];
      else
        for (std::size_t j = 0; j < 10; ++j)
          if (str.compare(i, hashmap[j].size(), hashmap[j]) == 0)
            res += std::to_string(j);
    }
    return res;
  }

  std::string remove_letters(const std::string &str)
  {
    std::string res;
    for (const auto &character : str)
      if (is_digit(character))
        res += character;
    return res;
  }
} // namespace

std::size_t aoc::day01::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  sum   = 0;
  for (const auto &elem : input)
  {
    std::string temp = remove_letters(elem);
    sum += get_digit(temp);
  }
  return sum;
}

std::size_t aoc::day01::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);

  std::size_t sum = 0;
  for (const auto &elem : input)
  {
    std::string temp = remove_letters(preprocess(elem));
    sum += get_digit(temp);
  }
  return sum;
}
