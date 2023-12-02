#include "aoc/solutions/day02.hpp"

#include "aoc/utils/parse.hpp"
#include <iostream>
#include <unordered_map>

static std::unordered_map<std::string, std::size_t> hashmap = {{"red", 12}, {"green", 13}, {"blue", 14}};

static bool is_game_feasible(const std::string &input)
{
  std::vector<std::string> game = aoc::parse::split_by_delimiter(input, ";");
  for (const auto &elem : game)
  {
    std::vector<std::string> temp = aoc::parse::split_by_delimiter(elem, ",");
    for (const auto &t : temp)
    {
      std::vector<std::string> cube_metadata = aoc::parse::split_by_delimiter(t, " ");
      if (hashmap[cube_metadata[1]] < std::stoull(cube_metadata[0])) return false;
    }
  }
  return true;
}

static std::size_t power(const std::string &input)
{
  std::unordered_map<std::string, std::size_t> memory = {{"red", 0}, {"green", 0}, {"blue", 0}};
  std::vector<std::string>                     game   = aoc::parse::split_by_delimiter(input, ";");
  for (const auto &elem : game)
  {
    std::vector<std::string> temp = aoc::parse::split_by_delimiter(elem, ",");
    for (const auto &t : temp)
    {
      std::vector<std::string> cube_metadata = aoc::parse::split_by_delimiter(t, " ");
      if (memory[cube_metadata[1]] < std::stoull(cube_metadata[0]))
        memory[cube_metadata[1]] = std::stoull(cube_metadata[0]);
    }
  }

  return memory["red"] * memory["green"] * memory["blue"];
}

std::size_t aoc::day02::part1(const std::string &filename)
{
  std::vector<std::string> input  = parse::cvt_file_to_vstring(filename);
  std::size_t              result = 0;
  for (std::size_t i = 0; i < input.size(); ++i)
  {
    std::vector<std::string> game = parse::split_by_delimiter(input[i], ":");
    if (is_game_feasible(game[1]))
      result += (i + 1);
  }
  return result;
}

std::size_t aoc::day02::part2(const std::string &filename)
{
  std::vector<std::string> input  = parse::cvt_file_to_vstring(filename);
  std::size_t              result = 0;
  for (std::size_t i = 0; i < input.size(); ++i)
  {
    std::vector<std::string> game = parse::split_by_delimiter(input[i], ":");
    result += power(game[1]);
  }
  return result;
}
