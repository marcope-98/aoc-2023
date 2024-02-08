#include "aoc/solutions/day18.hpp"

#include "aoc/utils/Point.hpp"
#include "aoc/utils/Polygon.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>

namespace
{
  struct Map
  {
    aoc::Polygon data;
    aoc::vstring view;

    void translate(const std::string &input)
    {
      aoc::vstring temp      = aoc::parse::split_by_delimiters(input, " ()#");
      std::string  hex       = temp.back();
      char         direction = hex.back();
      hex.pop_back();
      int        steps = std::stoul(hex, nullptr, 16);
      aoc::Point last  = this->data.empty() ? aoc::Point() : this->data.back();
      switch (direction)
      {
        case '0':
          last.x() += steps;
          break;
        case '1':
          last.y() += steps;
          break;
        case '2':
          last.x() -= steps;
          break;
        case '3':
          last.y() -= steps;
          break;
      }
      data.emplace_back(last);
    }

    void add(const std::string &input)
    {
      aoc::vstring temp  = aoc::parse::split_by_delimiters(input, " ");
      int          steps = std::stoi(temp[1]);
      aoc::Point   last  = this->data.empty() ? aoc::Point() : this->data.back();
      switch (temp[0].front())
      {
        case 'R':
          last.x() += steps;
          break;
        case 'D':
          last.y() += steps;
          break;
        case 'L':
          last.x() -= steps;
          break;
        case 'U':
          last.y() -= steps;
          break;
      }
      data.emplace_back(last);
    }

    std::size_t solve() { return this->data.area() + this->data.perimeter() / 2 + 1; }
  };

} // namespace

std::size_t aoc::day18::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map;

  for (const auto &line : input)
    map.add(line);

  return map.solve();
}

std::size_t aoc::day18::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map;
  for (const auto &line : input)
    map.translate(line);

  return map.solve();
}