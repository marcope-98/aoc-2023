#include "aoc/solutions/day10.hpp"

#include <algorithm>
#include <iostream>

#include "aoc/utils/Point.hpp"
#include "aoc/utils/Polygon.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  bool collinear(const aoc::Point &a, const aoc::Point &b, const aoc::Point &c) { return ((a.x() == b.x() && b.x() == c.x()) || (a.y() == b.y() && b.y() == c.y())); }

  aoc::Polygon simplify(const aoc::Polygon &polygon)
  {
    aoc::Polygon out;
    for (std::size_t i = 1; i < polygon.size() - 1; ++i)
      if (!collinear(polygon[i - 1], polygon[i], polygon[i + 1])) out.emplace_back(polygon[i]);
    if (!collinear(polygon[polygon.size() - 2], polygon.back(), polygon.front())) out.emplace_back(polygon.back());
    if (!collinear(polygon.back(), polygon.front(), polygon[1])) out.emplace_back(polygon.front());
    return out;
  }

  struct Maze
  {
    std::size_t  width;
    std::size_t  height;
    aoc::vstring map;

    Maze() = default;
    Maze(const aoc::vstring &input) : width{input[0].size()}, height{input.size()}, map(input)
    {
      map[0]     = aoc::parse::replace(map[0], "|LJ", '.');
      map.back() = aoc::parse::replace(map.back(), "|7F", '.');

      for (auto &line : map)
      {
        if (line.front() == '-' || line.front() == 'J' || line.front() == '7') line.front() = '.';
        if (line.back() == '-' || line.back() == 'L' || line.back() == 'F') line.back() = '.';
      }
    }

    char at(const aoc::Point &point) const { return this->map[point.y()][point.x()]; }

    aoc::Point get_start() const
    {
      aoc::Point point;
      for (std::size_t i = 0; i < this->height; ++i)
        for (std::size_t j = 0; j < this->width; ++j)
          if (this->map[i][j] == 'S')
            point = aoc::Point(j, i);
      return point;
    }

    std::string get_moves(const aoc::Point &point) const
    {
      std::string moves = "";
      if (point.x() != 0) moves += 'W';
      if (point.x() != (std::int64_t)this->width - 1) moves += 'E';
      if (point.y() != 0) moves += 'N';
      if (point.y() != (std::int64_t)this->height - 1) moves += 'S';
      return moves;
    }

    char update_move(const aoc::Point &point, const char &move) const
    {
      switch (this->at(point))
      {
        case '|':
        case '-':
          return move;
        case 'L':
          return move == 'S' ? 'E' : 'N';
        case 'J':
          return move == 'S' ? 'W' : 'N';
        case '7':
          return move == 'N' ? 'W' : 'S';
        case 'F':
          return move == 'N' ? 'E' : 'S';
        case '.':
          return '\0';
        default:
          return move;
      }
    }

    aoc::Point update_point(const aoc::Point &point, const char &move) const
    {
      switch (move)
      {
        case 'N':
          return {point.x(), point.y() - 1};
        case 'S':
          return {point.x(), point.y() + 1};
        case 'W':
          return {point.x() - 1, point.y()};
        case 'E':
          return {point.x() + 1, point.y()};
        default:
          return point;
      }
    }

    void step(aoc::Point &point, char &move) const
    {
      move  = this->update_move(point, move);
      point = this->update_point(point, move);
    }

    aoc::Polygon search() const
    {
      aoc::Point                start = this->get_start();
      std::string               moves = this->get_moves(start);
      std::vector<aoc::Polygon> polygons;
      for (const auto &init : moves)
      {
        aoc::Polygon temp;
        char         move  = init;
        aoc::Point   point = start;
        do
        {
          temp.emplace_back(point);
          this->step(point, move);
        } while (this->at(point) != 'S' && this->at(point) != '.');

        if (this->at(point) == 'S') polygons.emplace_back(temp);
      }

      return *std::max_element(polygons.begin(), polygons.end(),
                               [](const aoc::Polygon &a, const aoc::Polygon &b)
                               { return a.size() < b.size(); });
    }

    std::size_t solve(const aoc::Polygon &polygon) { return polygon.area() - polygon.perimeter() / 2 + 1; }
    void        remap(const aoc::Polygon &polygon)
    {
      for (auto &line : this->map)
        line = std::string(this->width, '.');
      for (const auto &point : polygon)
        this->map[point.y()][point.x()] = 'X';
    }
  };
} // namespace

std::size_t aoc::day10::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Maze         maze(input);
  return maze.search().size() / 2;
}

std::size_t aoc::day10::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Maze         maze(input);
  aoc::Polygon polygon = maze.search();
  maze.remap(polygon);
  polygon = simplify(polygon);

  std::size_t result = maze.solve(polygon);
  return result;
}
