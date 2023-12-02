#include "aoc/solutions/day02.hpp"

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

#include <unordered_map>

static std::unordered_map<std::string, std::size_t> hashmap = {{"red", 12}, {"green", 13}, {"blue", 14}};

static bool is_game_feasible(const std::string &input)
{
  aoc::vstring game = aoc::parse::split_by_delimiters(input, ";, ");
  for (std::size_t i = 0; i < game.size(); i += 2)
    if (hashmap[game[i + 1]] < std::stoull(game[i]))
      return false;
  return true;
}

static std::size_t power(const std::string &input)
{
  std::unordered_map<std::string, std::size_t> memory = {{"red", 0}, {"green", 0}, {"blue", 0}};

  aoc::vstring game = aoc::parse::split_by_delimiters(input, ";, ");
  for (std::size_t i = 0; i < game.size(); i += 2)
    if (memory[game[i + 1]] < std::stoull(game[i]))
      memory[game[i + 1]] = std::stoull(game[i]);

  return memory["red"] * memory["green"] * memory["blue"];
}

std::size_t aoc::day02::part1(const std::string &filename)
{
  aoc::vstring input  = parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;
  for (std::size_t i = 0; i < input.size(); ++i)
  {
    aoc::vstring game = parse::split_by_delimiters(input[i], ":");
    if (is_game_feasible(game[1]))
      result += (i + 1);
  }
  return result;
}

std::size_t aoc::day02::part2(const std::string &filename)
{
  aoc::vstring input  = parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;
  for (std::size_t i = 0; i < input.size(); ++i)
  {
    aoc::vstring game = parse::split_by_delimiters(input[i], ":");
    result += power(game[1]);
  }
  return result;
}
