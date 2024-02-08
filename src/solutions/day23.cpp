#include "aoc/solutions/day23.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>

#include "aoc/utils/Point.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  struct Path
  {
    std::size_t weight;
    aoc::Point  point;
    std::string to_string() const { return point.to_string() + "," + std::to_string(weight); }
  };

  struct Map
  {
    aoc::vstring                                       data;
    std::unordered_map<std::string, std::vector<Path>> graph;

    Map() = default;
    explicit Map(const aoc::vstring &input) : data(input)
    {
      this->graph[this->start().to_string()] = std::vector<Path>();
      this->graph[this->end().to_string()]   = std::vector<Path>();

      this->get_interest_points();
      this->generate_graph();
    }
    aoc::Point start() const { return aoc::Point((std::int64_t)this->data.front().find("."), 0); }
    aoc::Point end() const { return aoc::Point((std::int64_t)this->data.back().find("."), (std::int64_t)this->height() - 1); }

    std::size_t width() const { return this->data.front().size(); }
    std::size_t height() const { return this->data.size(); }

    bool in_bounds(const aoc::Point &point) const
    {
      return 0 <= point.x() && point.x() < (std::int64_t)this->width() &&
             0 <= point.y() && point.y() < (std::int64_t)this->height();
    }

    float solve(const aoc::Point &point)
    {
      if (point == this->end()) return 0;
      float m = -std::numeric_limits<float>::infinity();
      this->seen.insert(point.to_string());

      for (const auto &path : this->graph[point.to_string()])
        if (this->seen.find(path.point.to_string()) == this->seen.end())
          m = std::max(m, float(this->solve(path.point) + path.weight));

      for (auto it = this->seen.begin(); it != this->seen.end();)
        if (*it == point.to_string())
          it = this->seen.erase(it);
        else
          ++it;

      return m;
    }

    void get_interest_points()
    {
      aoc::Point moves[4] = {aoc::Point(-1, 0), aoc::Point(+1, 0), aoc::Point(0, -1), aoc::Point(0, +1)};
      for (std::size_t y = 0; y < this->height(); ++y)
        for (std::size_t x = 0; x < this->width(); ++x)
        {
          if (this->data[y][x] == '#') continue;
          std::size_t neighbors = 0;
          for (std::size_t i = 0; i < 4; ++i)
          {
            aoc::Point temp = aoc::Point(x, y) + moves[i];
            if (this->in_bounds(temp) && this->at(temp) != '#') neighbors++;
          }
          if (neighbors >= 3) this->graph[aoc::Point(x, y).to_string()] = std::vector<Path>();
        }
    }

    char at(const aoc::Point &point) const { return this->data[point.y()][point.x()]; }

    void generate_graph()
    {
      std::unordered_map<char, std::vector<aoc::Point>> moves = {{'^', {aoc::Point(0, -1)}},
                                                                 {'>', {aoc::Point(1, 0)}},
                                                                 {'<', {aoc::Point(-1, 0)}},
                                                                 {'v', {aoc::Point(0, 1)}},
                                                                 {'.', {aoc::Point(0, 1), aoc::Point(1, 0), aoc::Point(-1, 0), aoc::Point(0, -1)}}};

      for (const auto &key_value : this->graph)
      {
        std::string key = key_value.first;

        aoc::Point                      point(key);
        std::vector<Path>               stack = {Path{0, point}};
        std::unordered_set<std::string> seen;
        seen.insert(key);

        while (!stack.empty())
        {
          Path path = stack.back();
          stack.pop_back();
          if (path.weight != 0 && this->graph.find(path.point.to_string()) != this->graph.end())
          {
            this->graph[key].emplace_back(path);
            continue;
          }

          for (const auto &move : moves[this->at(path.point)])
          {
            aoc::Point pt = path.point + move;
            if (this->in_bounds(pt) && this->at(pt) != '#' && seen.find(pt.to_string()) == seen.end())
            {
              stack.emplace_back(Path{path.weight + 1, pt});
              seen.insert(pt.to_string());
            }
          }
        }
      }
    }

  private:
    std::unordered_set<std::string> seen;
  };
} // namespace

std::size_t aoc::day23::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map(input);
  return map.solve(map.start());
}

std::size_t aoc::day23::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  for (auto &line : input)
    for (auto &character : line)
      if (character != '#' && character != '.')
        character = '.';

  Map map(input);
  return std::size_t(map.solve(map.start()));
}