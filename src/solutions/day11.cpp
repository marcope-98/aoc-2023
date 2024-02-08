#include "aoc/solutions/day11.hpp"

#include <iostream>

#include "aoc/utils/Point.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  struct Universe
  {
    std::vector<aoc::Point> nodes;
    std::size_t             delta;

    Universe() = default;
    Universe(const aoc::vstring &input, const std::size_t &increment) : delta{increment}
    {
      const std::size_t height = input.size();
      const std::size_t width  = input[0].size();
      for (std::size_t i = 0; i < height; ++i)
        for (std::size_t j = 0; j < width; ++j)
          if (input[i][j] == '#')
            this->nodes.emplace_back(aoc::Point(j, i));

      this->expand(input);
    }

    std::size_t shortest_path(const std::size_t start) const
    {
      std::size_t result = 0;
      for (std::size_t i = start + 1; i < this->nodes.size(); ++i)
        result += (this->nodes[start] - this->nodes[i]).abs().sum();
      return result;
    }

    static std::vector<std::size_t> has_empty_string(const aoc::vstring &input, const std::string &empty_string)
    {
      std::vector<std::size_t> out;
      for (std::size_t i = 0; i < input.size(); ++i)
        if (input[i] == empty_string) out.emplace_back(i);
      return out;
    }

    void expand(const aoc::vstring &input)
    {
      std::vector<std::size_t> rows = this->has_empty_string(input, std::string(input[0].size(), '.'));
      std::vector<std::size_t> cols = this->has_empty_string(aoc::parse::transpose(input), std::string(input.size(), '.'));

      for (int i = rows.size() - 1; i >= 0; --i)
        for (auto &node : this->nodes)
          if ((std::int64_t)rows[i] < node.y())
            node.y() += this->delta;

      for (int i = cols.size() - 1; i >= 0; --i)
        for (auto &node : this->nodes)
          if ((std::int64_t)cols[i] < node.x())
            node.x() += this->delta;
    }
  };
} // namespace

std::size_t aoc::day11::part1(const std::string &filename, const std::size_t &increment)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);

  Universe    universe(input, increment - 1);
  std::size_t result = 0;
  for (std::size_t i = 0; i < universe.nodes.size(); ++i)
    result += universe.shortest_path(i);
  return result;
}

std::size_t aoc::day11::part2(const std::string &filename, const std::size_t &increment)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Universe     universe(input, increment - 1);
  std::size_t  result = 0;
  for (std::size_t i = 0; i < universe.nodes.size(); ++i)
    result += universe.shortest_path(i);

  return result;
}