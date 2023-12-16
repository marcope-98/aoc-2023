#include "aoc/solutions/day14.hpp"

#include <iostream>
#include <unordered_map>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

struct Map
{
  aoc::vstring data;

  Map() = default;
  explicit Map(const aoc::vstring &input) : data(input)
  {
    this->data = aoc::parse::flipud(aoc::parse::transpose(this->data)); // counter clockwise
  }

  std::string to_string() const { return aoc::parse::concatenate(this->data); }

  void tilt()
  {
    this->ragged_left();
    this->data = aoc::parse::fliplr(aoc::parse::transpose(this->data)); // clockwise
  }

  void ragged_left()
  {
    for (auto &line : this->data)
    {
      auto at = line.begin();
      for (auto it = line.begin(); it != line.end();)
      {
        switch (*it)
        {
          case 'O':
            *at++ = *it++;
            break;
          case '#':
            if (*at == '#')
              *at++ = *it++;
            else
              *at++ = '.';
            break;
          default:
            it++;
            break;
        }
      }
      while (at != line.end())
        *at++ = '.';
    }
  }

  std::size_t load() const
  {
    std::size_t result = 0;
    for (const auto &line : this->data)
      for (std::size_t i = 0; i < line.size(); ++i)
        if (line[i] == 'O')
          result += line.size() - i;
    return result;
  }

  void cycle()
  {
    for (std::size_t i = 0; i < 4; ++i)
      this->tilt();
  }

  void print() const
  {
    aoc::vstring temp(this->data);
    temp = aoc::parse::fliplr(aoc::parse::transpose(temp));
    for (const auto &line : temp)
      std::cerr << line << "\n";
  }
};

std::size_t aoc::day14::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map(input);
  map.ragged_left();
  return map.load();
}

std::size_t aoc::day14::part2(const std::string &filename, const std::size_t &cycles)
{
  aoc::vstring                                 input = aoc::parse::cvt_file_to_vstring(filename);
  std::unordered_map<std::string, std::size_t> memory;
  std::vector<std::size_t>                     loads;

  Map map(input);

  memory[map.to_string()] = 0;
  loads.emplace_back(map.load());
  for (std::size_t i = 0; i < cycles; ++i)
  {
    map.cycle();
    if (memory.find(map.to_string()) != memory.end())
      break;
    else
    {
      memory[map.to_string()] = loads.size();
      loads.emplace_back(map.load());
    }
  }

  std::size_t begin = memory[map.to_string()];
  std::size_t end   = loads.size();
  return loads[((cycles - begin) % (end - begin)) + begin];
}