#include "aoc/solutions/day16.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

struct Beam
{
  char        dir;
  std::size_t x;
  std::size_t y;

  void update()
  {
    switch (this->dir)
    {
      case 'N':
        this->y -= 1;
        break;
      case 'E':
        this->x += 1;
        break;
      case 'W':
        this->x -= 1;
        break;
      case 'S':
        this->y += 1;
        break;
    }
  }

  std::string hash() const
  {
    return std::string(1, this->dir) + "," + std::to_string(this->x) + "," + std::to_string(this->y);
  }
};

struct Map
{
  aoc::vstring                          map;
  aoc::vstring                          energized_map;
  std::unordered_map<std::string, bool> hashmap;
  std::vector<Beam>                     beams;

  Map() = default;
  Map(const aoc::vstring &input, const std::size_t &width, const std::size_t &height) : map{input}
  {
    for (std::size_t i = 0; i < height; ++i)
      this->energized_map.emplace_back(std::string(width, '.'));
    this->beams.emplace_back(Beam{'E', 0, 0});
  }
  Map(const aoc::vstring &input, const std::size_t &width, const std::size_t &height, const Beam &start) : map{input}
  {
    for (std::size_t i = 0; i < height; ++i)
      this->energized_map.emplace_back(std::string(width, '.'));
    this->beams.emplace_back(start);
  }

  void update_dirs()
  {
    std::size_t size = this->beams.size();
    for (std::size_t i = 0; i < size; ++i)
    {
      this->hashmap[this->beams[i].hash()] = true;
      switch (this->map[this->beams[i].y][this->beams[i].x])
      {
        case '|':
          if (this->beams[i].dir != 'N' && this->beams[i].dir != 'S')
          {
            this->beams[i].dir = 'N';
            this->beams.emplace_back(Beam{'S', this->beams[i].x, this->beams[i].y});
          }
          break;
        case '-':
          if (this->beams[i].dir != 'E' && this->beams[i].dir != 'W')
          {
            this->beams[i].dir = 'E';
            this->beams.emplace_back(Beam{'W', this->beams[i].x, this->beams[i].y});
          }
          break;
        case '/':
          if (this->beams[i].dir == 'E' || this->beams[i].dir == 'S')
            this->beams[i].dir = (this->beams[i].dir == 'E') ? 'N' : 'W';
          else
            this->beams[i].dir = (this->beams[i].dir == 'N') ? 'E' : 'S';
          break;
        case '\\':
          if (this->beams[i].dir == 'N' || this->beams[i].dir == 'E')
            this->beams[i].dir = (this->beams[i].dir == 'N') ? 'W' : 'S';
          else
            this->beams[i].dir = (this->beams[i].dir == 'S') ? 'E' : 'N';
          break;
      }
      this->energized_map[this->beams[i].y][this->beams[i].x] = '#';
    }
  }

  void update_points()
  {
    for (auto &beam : this->beams)
      beam.update();
  }

  void delete_inactive_beams()
  {
    for (auto it = this->beams.begin(); it != beams.end();)
    {
      if (it->x >= this->map.front().size() ||
          it->y >= this->map.size() ||
          this->hashmap.find(it->hash()) != this->hashmap.end())
        it = this->beams.erase(it);
      else
        ++it;
    }
  }

  void step()
  {
    this->update_dirs();
    this->update_points();
    this->delete_inactive_beams();
  }

  std::size_t solve() const
  {
    std::size_t result = 0;
    for (const auto &line : this->energized_map)
      for (const auto &character : line)
        if (character == '#')
          result++;
    return result;
  }
};

std::size_t aoc::day16::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map(input, input[0].size(), input.size());
  while (!map.beams.empty())
    map.step();

  return map.solve();
}

std::size_t aoc::day16::part2(const std::string &filename)
{
  aoc::vstring input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;
  std::size_t  width  = input[0].size();
  std::size_t  height = input.size();

  for (std::size_t i = 0; i < width; ++i)
  {
    Map map(input, width, height, Beam{'S', i, 0});
    while (!map.beams.empty())
      map.step();
    if (result < map.solve()) result = map.solve();
  }

  for (std::size_t i = 0; i < width; ++i)
  {
    Map map(input, width, height, Beam{'N', i, height - 1});
    while (!map.beams.empty())
      map.step();
    if (result < map.solve()) result = map.solve();
  }

  for (std::size_t i = 0; i < height; ++i)
  {
    Map map(input, width, height, Beam{'E', 0, i});
    while (!map.beams.empty())
      map.step();
    if (result < map.solve()) result = map.solve();
  }

  for (std::size_t i = 0; i < height; ++i)
  {
    Map map(input, width, height, Beam{'W', width - 1, i});
    while (!map.beams.empty())
      map.step();
    if (result < map.solve()) result = map.solve();
  }

  return result;
}