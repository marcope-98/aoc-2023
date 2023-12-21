#include "aoc/solutions/day05.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "aoc/utils/Range.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"
namespace
{
  struct Map
  {
    std::vector<aoc::Range> seeds;
    std::vector<aoc::Range> sources;
    std::vector<aoc::Range> destinations;

    void generate_new_ranges()
    {
      std::size_t size = this->seeds.size();
      for (std::size_t i = 0; i < size; ++i)
        for (const auto &source : this->sources)
        {
          std::vector<aoc::Range> temp = this->seeds[i].split(source);
          this->seeds[i]               = temp[0];
          for (std::size_t i = 1; i < temp.size(); ++i)
          {
            size++;
            this->seeds.emplace_back(temp[i]);
          }
        }
    }

    void transform()
    {
      for (auto &seed : this->seeds)
        for (std::size_t i = 0; i < this->sources.size(); ++i)
          if (this->sources[i].contains(seed))
          {
            seed = (seed - this->sources[i].begin()) + this->destinations[i].begin();
            break;
          }
    }

    void apply()
    {
      this->generate_new_ranges();
      this->transform();
    }

    void handle_seeds(const aoc::vstring &input, bool part1 = true)
    {
      if (part1)
        for (std::size_t i = 1; i < input.size(); ++i)
          this->seeds.emplace_back(aoc::Range(std::stoull(input[i]), std::stoull(input[i])));
      else
        for (std::size_t i = 1; i < input.size(); i += 2)
          this->seeds.emplace_back(aoc::Range(std::stoull(input[i]),
                                              std::stoull(input[i]) + std::stoull(input[i + 1]) - 1));
    }

    void handle_range(const aoc::Range &source, const aoc::Range &destination)
    {
      this->sources.emplace_back(source);
      this->destinations.emplace_back(destination);
    }

    void handle_header()
    {
      this->sources.clear();
      this->destinations.clear();
    }
  };

  static void get_ranges(const aoc::vstring &input, aoc::Range &source, aoc::Range &destination)
  {
    destination.begin() = std::stoull(input[0]);
    source.begin()      = std::stoull(input[1]);
    std::size_t length  = std::stoull(input[2]);
    destination.end()   = destination.begin() + length - 1;
    source.end()        = source.begin() + length - 1;
  }
} // namespace

std::size_t aoc::day05::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map;
  aoc::Range   source, destination;
  for (const auto &line : input)
  {
    aoc::vstring temp = aoc::parse::split_by_delimiters(line, " ");
    switch (temp.size())
    {
      case 0: // empty line
        map.apply();
        break;
      case 2: // header
        map.handle_header();
        break;
      case 3: // range
        get_ranges(temp, source, destination);
        map.handle_range(source, destination);
        break;
      default:
        map.handle_seeds(temp);
        break;
    }
  }
  map.apply();

  return std::min_element(map.seeds.begin(), map.seeds.end(),
                          [](const aoc::Range &a, const aoc::Range &b)
                          { return a.begin() < b.begin(); })
      ->begin();
}

std::size_t aoc::day05::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map;
  aoc::Range   source, destination;
  for (const auto &line : input)
  {
    aoc::vstring temp = aoc::parse::split_by_delimiters(line, " ");
    switch (temp.size())
    {
      case 0: // empty line
        map.apply();
        break;
      case 2: // header
        map.handle_header();
        break;
      case 3: // range
        get_ranges(temp, source, destination);
        map.handle_range(source, destination);
        break;
      default: // seeds
        map.handle_seeds(temp, false);
        break;
    }
  }
  map.apply();

  return std::min_element(map.seeds.begin(), map.seeds.end(),
                          [](const aoc::Range &a, const aoc::Range &b)
                          { return a.begin() < b.begin(); })
      ->begin();
}