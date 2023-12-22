#include "aoc/solutions/day18.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>

namespace
{
  struct Point
  {
    std::int64_t x;
    std::int64_t y;
  };

  using Polygon = std::vector<Point>;

  int orientation(const Point &a, const Point &b, const Point &c)
  {
    std::int64_t temp = ((b.y - a.y) * (c.x - b.x)) - ((b.x - a.x) * (c.y - b.y));
    return int(temp > 0) - int(temp < 0);
  }

  std::int64_t perimeter(const Polygon &polygon)
  {
    std::int64_t res  = 0;
    std::int64_t temp = 0;
    for (std::size_t i = 0; i < polygon.size() - 1; ++i)
    {
      temp = (polygon[i].x - polygon[i + 1].x) + (polygon[i].y - polygon[i + 1].y);
      res += temp > 0 ? temp : -temp;
    }
    temp = (polygon.front().x - polygon.back().x) + (polygon.front().y - polygon.back().y);
    res += temp > 0 ? temp : -temp;
    return res;
  }

  int vertex_type(const Polygon &polygon)
  {
    int res = 0;
    res += orientation(polygon.back(), polygon.front(), polygon[1]);
    for (std::size_t i = 1; i < polygon.size() - 1; ++i)
      res += orientation(polygon[i - 1], polygon[i], polygon[i + 1]);

    res += orientation(polygon[polygon.size() - 2], polygon.back(), polygon.front());
    return -res;
  }

  std::int64_t area(const Polygon &polygon)
  {
    std::int64_t res = 0;
    for (std::size_t i = 0; i < polygon.size() - 1; ++i)
      res += (std::int64_t(polygon[i].x) * std::int64_t(polygon[i + 1].y) - std::int64_t(polygon[i + 1].x) * std::int64_t(polygon[i].y));
    res += (std::int64_t(polygon.back().x) * std::int64_t(polygon.front().y) - std::int64_t(polygon.front().x) * std::int64_t(polygon.back().y));

    return res > 0 ? res / 2 : -res / 2;
  }

  struct Map
  {
    Polygon      data;
    aoc::vstring view;

    void translate(const std::string &input)
    {
      aoc::vstring temp      = aoc::parse::split_by_delimiters(input, " ()#");
      std::string  hex       = temp.back();
      char         direction = hex.back();
      hex.pop_back();
      int   steps = std::stoul(hex, nullptr, 16);
      Point last  = this->data.empty() ? Point{0, 0} : this->data.back();
      switch (direction)
      {
        case '0':
          last.x += steps;
          break;
        case '1':
          last.y += steps;
          break;
        case '2':
          last.x -= steps;
          break;
        case '3':
          last.y -= steps;
          break;
      }
      data.emplace_back(last);
    }

    void add(const std::string &input)
    {
      aoc::vstring temp  = aoc::parse::split_by_delimiters(input, " ");
      int          steps = std::stoi(temp[1]);
      Point        last  = this->data.empty() ? Point{0, 0} : this->data.back();
      switch (temp[0].front())
      {
        case 'R':
          last.x += steps;
          break;
        case 'D':
          last.y += steps;
          break;
        case 'L':
          last.x -= steps;
          break;
        case 'U':
          last.y -= steps;
          break;
      }
      data.emplace_back(last);
    }

    std::size_t solve()
    {
      std::int64_t diff = vertex_type(this->data);
      return area(this->data) + (2 * perimeter(this->data) + diff) / 4;
    }
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