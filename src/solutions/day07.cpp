#include "aoc/solutions/day07.hpp"

#include <algorithm>
#include <iostream>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  enum HandType
  {
    FIVE_OF_A_KIND  = 0,
    FOUR_OF_A_KIND  = 1,
    FULL_HOUSE      = 2,
    THREE_OF_A_KIND = 3,
    TWO_PAIR        = 4,
    ONE_PAIR        = 5,
    HIGH_CARD       = 6,
  };

  std::unordered_map<char, std::size_t> values;

  void set_values(const std::string &ascending_values)
  {
    for (std::size_t i = 0; i < ascending_values.size(); ++i)
      values[ascending_values[i]] = i;
  }
  std::size_t get_value(const char &character) { return values[character]; }

  struct Hand
  {
    std::string hand;
    HandType    type;
    std::size_t bid{0};
    std::size_t hashmap[13] = {0};

    Hand() = default;
    Hand(const std::string &hand_, const std::size_t &bid_) : hand{hand_}, bid{bid_}
    {
      this->type = get_type();
    }

    HandType get_type()
    {
      for (const auto &elem : this->hand)
        this->hashmap[get_value(elem)]++;

      std::size_t count = 0;
      std::size_t max   = 0;
      for (std::size_t i = 0; i < 13; ++i)
      {
        if (max < this->hashmap[i]) max = this->hashmap[i];
        count += int(this->hashmap[i] != 0);
      }

      if (count < 3)
        return static_cast<HandType>(count - std::size_t(max != 3));
      else
        return static_cast<HandType>(count + std::size_t(max != 3));
    };

    void handle_jokers()
    {
      if (this->hashmap[get_value('J')] == 0) return;

      switch (this->type)
      {
        case FIVE_OF_A_KIND: // 0
        case FOUR_OF_A_KIND: // 1
        case FULL_HOUSE:     // 2
          this->type = FIVE_OF_A_KIND;
          break;
        case THREE_OF_A_KIND: // 3
          this->type = FOUR_OF_A_KIND;
          break;
        case TWO_PAIR: // 4
          if (this->hashmap[get_value('J')] == 1)
            this->type = FULL_HOUSE;
          else
            this->type = FOUR_OF_A_KIND;
          break;
        case ONE_PAIR: // 5
          this->type = THREE_OF_A_KIND;
          break;
        case HIGH_CARD: // 6
          this->type = ONE_PAIR;
          break;
      }
    }

    bool operator<(const Hand &hand) const
    {
      if (this->type == hand.type)
      {
        for (std::size_t i = 0; i < this->hand.size(); ++i)
          if (get_value(this->hand[i]) == get_value(hand.hand[i]))
            continue;
          else
            return get_value(this->hand[i]) < get_value(hand.hand[i]);
      }
      return this->type > hand.type; // counter intuitive
    }
  };
} // namespace

std::size_t aoc::day07::part1(const std::string &filename)
{
  aoc::vstring      input = aoc::parse::cvt_file_to_vstring(filename);
  std::vector<Hand> hands;
  set_values("23456789TJQKA");
  for (const auto &line : input)
  {
    aoc::vstring temp = aoc::parse::split_by_delimiters(line, " ");
    hands.emplace_back(Hand(temp[0], std::stoull(temp[1])));
  }

  std::sort(hands.begin(), hands.end(), [](const Hand &a, const Hand &b)
            { return a < b; });

  std::size_t result = 0;
  for (std::size_t i = 0; i < hands.size(); ++i)
    result += hands[i].bid * (i + 1);

  return result;
}

std::size_t aoc::day07::part2(const std::string &filename)
{
  aoc::vstring      input = aoc::parse::cvt_file_to_vstring(filename);
  std::vector<Hand> hands;
  set_values("J23456789TQKA");

  for (const auto &line : input)
  {
    aoc::vstring temp = aoc::parse::split_by_delimiters(line, " ");
    hands.emplace_back(Hand(temp[0], std::stoull(temp[1])));
  }
  for (auto &elem : hands)
    elem.handle_jokers();

  std::sort(hands.begin(), hands.end(), [](const Hand &a, const Hand &b)
            { return a < b; });

  std::size_t result = 0;
  for (std::size_t i = 0; i < hands.size(); ++i)
    result += hands[i].bid * (i + 1);

  return result;
}