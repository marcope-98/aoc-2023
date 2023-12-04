#include "aoc/solutions/day04.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

static std::size_t matches(std::vector<std::size_t> &card)
{
  std::size_t temp = card.size();
  std::sort(card.begin(), card.end());
  card.erase(std::unique(card.begin(), card.end()), card.end());
  return (temp - card.size());
}

std::size_t aoc::day04::part1(const std::string &filename)
{
  aoc::vstring             input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t              result = 0;
  std::vector<std::size_t> card;
  for (const auto &line : input)
  {
    aoc::vstring temp = aoc::parse::split_by_delimiters(line, ":| ");
    card.clear();
    card.reserve(temp.size() - 2);
    for (std::size_t i = 2; i < temp.size(); ++i)
      card.emplace_back(std::stoull(temp[i]));

    std::size_t value = matches(card);
    if (value != 0) result += (1 << (value - 1));
  }

  return result;
}

std::size_t aoc::day04::part2(const std::string &filename)
{
  aoc::vstring             input = aoc::parse::cvt_file_to_vstring(filename);
  std::vector<std::size_t> scratchcards;
  std::vector<std::size_t> card;
  for (const auto &line : input)
  {
    aoc::vstring temp = aoc::parse::split_by_delimiters(line, ":| ");
    card.clear();
    card.reserve(temp.size() - 2);
    for (std::size_t i = 2; i < temp.size(); ++i)
      card.emplace_back(std::stoull(temp[i]));

    scratchcards.emplace_back(matches(card));
  }

  card.clear();
  card.resize(scratchcards.size(), 1);
  for (std::size_t i = 0; i < scratchcards.size(); ++i)
    for (std::size_t j = 1; j <= scratchcards[i]; ++j)
      card[i + j] += card[i];

  return std::accumulate(card.begin(), card.end(), 0);
}