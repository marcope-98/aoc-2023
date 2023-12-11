#include "aoc/solutions/day10.hpp"

#include <algorithm>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

struct Point
{
  std::size_t x = 0;
  std::size_t y = 0;
};

using Polygon = std::vector<Point>;

static bool collinear(const Point &a, const Point &b, const Point &c) { return ((a.x == b.x && b.x == c.x) || (a.y == b.y && b.y == c.y)); }

static Polygon simplify(const Polygon &polygon)
{
  Polygon out;
  for (std::size_t i = 1; i < polygon.size() - 1; ++i)
    if (!collinear(polygon[i - 1], polygon[i], polygon[i + 1]))
      out.emplace_back(polygon[i]);
  if (!collinear(polygon[polygon.size() - 2], polygon.back(), polygon.front()))
    out.emplace_back(polygon.back());
  if (!collinear(polygon.back(), polygon[0], polygon[1]))
    out.emplace_back(polygon[0]);
  return out;
}

static bool intersects(const Point &point, const Point &edge1, const Point &edge2) { return (edge1.y < point.y && point.y < edge2.y) || (edge2.y < point.y && point.y < edge1.y); }

static bool inside(const Point &point, const Polygon &polygon)
{
  std::size_t intersections = 0;
  for (std::size_t i = 0; i < polygon.size() - 1; ++i)
  {
    if (polygon[i].x > point.x)
    {
      if (collinear(point, polygon[i], polygon[i + 1]))
      {
        Point edge1 = (i == 0) ? polygon.back() : polygon[i - 1];
        Point edge2 = (i == polygon.size() - 2) ? polygon.front() : polygon[i + 2];
        intersections += std::size_t(intersects(point, edge1, edge2));
      }
      else
        intersections += std::size_t(intersects(point, polygon[i], polygon[i + 1]));
    }
  }
  // repeat for last point and first point
  if (polygon.back().x > point.x)
  {
    if (collinear(point, polygon.back(), polygon.front()))
      intersections += std::size_t(intersects(point, polygon[1], polygon[polygon.size() - 2]));
    else
      intersections += std::size_t(intersects(point, polygon.back(), polygon.front()));
  }
  return intersections % 2 != 0;
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

  char at(const Point &point) const { return this->map[point.y][point.x]; }

  Point get_start() const
  {
    Point point;
    for (std::size_t i = 0; i < this->height; ++i)
      for (std::size_t j = 0; j < this->width; ++j)
        if (this->map[i][j] == 'S')
          point = {j, i};
    return point;
  }

  std::string get_moves(const Point &point) const
  {
    std::string moves = "";
    if (point.x != 0) moves += 'W';
    if (point.x != this->width - 1) moves += 'E';
    if (point.y != 0) moves += 'N';
    if (point.y != this->height - 1) moves += 'S';
    return moves;
  }

  char update_move(const Point &point, const char &move) const
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

  Point update_point(const Point &point, const char &move) const
  {
    switch (move)
    {
      case 'N':
        return {point.x, point.y - 1};
      case 'S':
        return {point.x, point.y + 1};
      case 'W':
        return {point.x - 1, point.y};
      case 'E':
        return {point.x + 1, point.y};
      default:
        return point;
    }
  }

  void step(Point &point, char &move) const
  {
    move  = this->update_move(point, move);
    point = this->update_point(point, move);
  }

  Polygon search() const
  {
    Point                start = this->get_start();
    std::string          moves = this->get_moves(start);
    std::vector<Polygon> polygons;
    for (const auto &init : moves)
    {
      Polygon temp;
      char    move  = init;
      Point   point = start;
      do
      {
        temp.emplace_back(point);
        this->step(point, move);
      } while (this->at(point) != 'S' && this->at(point) != '.');

      if (this->at(point) == 'S') polygons.emplace_back(temp);
    }

    return *std::max_element(polygons.begin(), polygons.end(),
                             [](const Polygon &a, const Polygon &b)
                             { return a.size() < b.size(); });
  }

  std::size_t solve(const Polygon &polygon)
  {
    std::size_t result = 0;
    for (std::size_t i = 0; i < this->height; ++i)
      for (std::size_t j = 0; j < this->width; ++j)
        if (this->map[i][j] == '.' && inside({j, i}, polygon))
          result++;
    return result;
  }
  void remap(const Polygon &polygon)
  {
    for (auto &line : this->map)
      line = std::string(this->width, '.');
    for (const auto &point : polygon)
      this->map[point.y][point.x] = 'X';
  }
};

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
  Polygon      polygon = maze.search();
  maze.remap(polygon);
  polygon = simplify(polygon);

  std::size_t result = maze.solve(polygon);
  return result;
}