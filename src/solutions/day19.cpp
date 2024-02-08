#include "aoc/solutions/day19.hpp"

#include "aoc/utils/Range.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

#include <functional>
#include <iostream>
#include <unordered_map>

namespace
{
  // clang-format off
  auto lt = [](const std::size_t &lhs, const std::size_t &rhs) { return lhs < rhs; };
  auto gt = [](const std::size_t &lhs, const std::size_t &rhs) { return lhs > rhs; };
  std::unordered_map<char, std::function<bool(const std::size_t &, const std::size_t &)>> ops = {{'>', gt}, {'<', lt}};
  // clang-format on

  struct Item : public std::unordered_map<char, std::size_t>
  {
    explicit Item(const std::string &input)
    {
      aoc::vstring temp = aoc::parse::split_by_delimiters(input, "{=,}");
      for (std::size_t i = 0; i < temp.size(); i += 2)
        this->insert({temp[i].front(), std::stoull(temp[i + 1])});
    }

    std::size_t sum() const
    {
      std::size_t result = 0;
      for (auto it = this->cbegin(); it != this->cend(); ++it)
        result += it->second;
      return result;
    }
  };

  struct Workshops : public std::unordered_map<std::string, aoc::vstring>
  {
    void add(const std::string &input)
    {
      aoc::vstring temp = aoc::parse::split_by_delimiters(input, "{},:");
      std::string  name = temp.front();
      temp.erase(temp.begin());
      this->insert({name, temp});
    }

    bool accept_item(const Item &item, const std::string &name = "in") const
    {
      if (name == "R") return false;
      if (name == "A") return true;

      aoc::vstring rules = this->at(name);
      for (std::size_t i = 0; i < rules.size() - 1; i += 2)
      {
        std::size_t lhs = item.at(rules[i][0]);
        char        op  = rules[i][1];
        std::string rhs = rules[i].substr(2);
        if (ops[op](lhs, std::stoull(rhs)))
          return accept_item(item, rules[i + 1]);
      }
      return accept_item(item, rules.back());
    }

    std::size_t count(std::unordered_map<char, aoc::Range> &ranges, const std::string &name = "in") const
    {
      if (name == "R") return 0;
      if (name == "A")
      {
        std::size_t product = 1;
        for (const auto &range : ranges)
          product *= range.second.end() - range.second.begin() + 1;
        return product;
      }
      std::size_t  total  = 0;
      aoc::vstring rules  = this->at(name);
      bool         broken = false;
      for (std::size_t i = 0; i < rules.size() - 1; i += 2)
      {
        char        key   = rules[i][0];
        char        cmp   = rules[i][1];
        std::string rhs   = rules[i].substr(2);
        aoc::Range  range = ranges.at(key);
        aoc::Range  accept, reject;
        if (cmp == '<')
        {
          accept = aoc::Range(range.begin(), std::stoull(rhs) - 1);
          reject = aoc::Range(std::stoull(rhs), range.end());
        }
        else
        {
          accept = aoc::Range(std::stoull(rhs) + 1, range.end());
          reject = aoc::Range(range.begin(), std::stoull(rhs));
        }
        if (accept.begin() <= accept.end())
        {
          std::unordered_map<char, aoc::Range> copy(ranges);
          copy[key] = accept;
          total += this->count(copy, rules[i + 1]);
        }
        if (reject.begin() <= reject.end())
        {
          ranges[key] = reject;
        }
        else
        {
          broken = true;
          break;
        }
      }
      if (!broken) total += count(ranges, rules.back());

      return total;
    }
  };
} // namespace

std::size_t aoc::day19::part1(const std::string &filename)
{
  aoc::vstring input      = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  empty_line = aoc::parse::empty_line_pos(input);

  Workshops workshops;
  for (std::size_t line = 0; line < empty_line; ++line)
    workshops.add(input[line]);

  std::size_t result = 0;
  for (std::size_t line = empty_line + 1; line < input.size(); ++line)
  {
    Item item(input[line]);
    if (workshops.accept_item(item))
      result += item.sum();
  }
  return result;
}

std::size_t aoc::day19::part2(const std::string &filename)
{
  aoc::vstring input      = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  empty_line = aoc::parse::empty_line_pos(input);

  Workshops workshops;
  for (std::size_t line = 0; line < empty_line; ++line)
    workshops.add(input[line]);
  std::unordered_map<char, aoc::Range> ranges = {{'x', aoc::Range(1, 4000)},
                                                 {'m', aoc::Range(1, 4000)},
                                                 {'a', aoc::Range(1, 4000)},
                                                 {'s', aoc::Range(1, 4000)}};

  return workshops.count(ranges);
}