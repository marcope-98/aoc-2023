#include "aoc/solutions/day09.hpp"

#include <iostream>
#include <vector>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  bool all_zeros(const std::vector<int> &input)
  {
    for (const auto &elem : input)
      if (elem != 0)
        return false;
    return true;
  }

  struct Sequence
  {
    std::vector<int> data;

    Sequence() = default;
    explicit Sequence(const std::string &input, bool front = false)
    {
      aoc::vstring     temp = aoc::parse::split_by_delimiters(input, " ");
      std::vector<int> history, diff;
      history.reserve(temp.size());

      for (const auto &str : temp)
        history.emplace_back(std::stoi(str));

      while (!all_zeros(history))
      {
        this->data.emplace_back(front ? history.front() : history.back());
        diff.clear();
        for (std::size_t i = 0; i < history.size() - 1; ++i)
          diff.emplace_back(history[i + 1] - history[i]);
        std::swap(diff, history);
      }
    }

    int solve_back()
    {
      int placeholder = 0;
      for (const auto &elem : this->data)
        placeholder += elem;
      return placeholder;
    }

    int solve_front()
    {
      bool positive    = true;
      int  placeholder = 0;
      for (const auto &elem : this->data)
      {
        placeholder += positive ? elem : -elem;
        positive = !positive;
      }
      return placeholder;
    }
  };
} // namespace

std::size_t aoc::day09::part1(const std::string &filename)
{
  aoc::vstring input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;
  for (const auto &line : input)
  {
    Sequence sequence(line, false);
    result += sequence.solve_back();
  }

  return result;
}

std::size_t aoc::day09::part2(const std::string &filename)
{
  aoc::vstring input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;

  for (const auto &line : input)
  {
    Sequence sequence(line, true);
    result += sequence.solve_front();
  }
  return result;
}