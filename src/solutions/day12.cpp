#include "aoc/solutions/day12.hpp"

#include <unordered_map>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  struct Record
  {
    std::vector<std::size_t>                     groups;
    std::string                                  base;
    std::unordered_map<std::string, std::size_t> memory;

    Record() = default;
    Record(const std::string &input, const std::size_t &copies)
    {
      aoc::vstring temp = aoc::parse::split_by_delimiters(input, ", ");
      this->base        = temp.front();
      this->groups.reserve(temp.size() - 1);
      for (std::size_t i = 1; i < temp.size(); ++i)
        if (std::stoull(temp[i]) != 0)
          this->groups.emplace_back(std::stoull(temp[i]));
      std::vector<std::size_t> groups_copy(this->groups);
      std::string              base_copy = this->base;
      for (std::size_t i = 0; i < copies - 1; ++i)
      {
        for (const auto &group : groups_copy)
          this->groups.emplace_back(group);
        this->base += "?" + base_copy;
      }

      this->simplify();
    }

    void simplify()
    {
      aoc::vstring temp = aoc::parse::split_by_delimiters(this->base, ".");
      while (!this->groups.empty() &&
             temp.back().find('#') != std::string::npos &&
             temp.back().size() == this->groups.back())
      {
        temp.pop_back();
        this->groups.pop_back();
      }

      while (!this->groups.empty() &&
             temp.front().find('#') != std::string::npos &&
             temp.front().size() == this->groups.front())
      {
        temp.erase(temp.begin());
        this->groups.erase(this->groups.begin());
      }

      this->base = ".";
      for (const auto &str : temp)
        this->base += str + ".";
    }

    std::size_t arrangements(const std::size_t &i, const std::size_t &j)
    {
      // if no more character in this->base
      if (i == this->base.size()) return j == this->groups.size() ? 1 : 0;
      // if no more group in this->groups
      if (j == this->groups.size())
      {
        std::string temp = this->base.substr(i);
        return temp.find('#') == std::string::npos ? 1 : 0;
      }

      std::string key = std::to_string(i) + "," + std::to_string(j);
      if (this->memory.find(key) != this->memory.end()) return this->memory[key];

      std::size_t result = 0;
      if (this->base[i] == '.' || this->base[i] == '?')
        result += this->arrangements(i + 1, j);
      if (this->base[i] == '#' || this->base[i] == '?')
      {
        std::string temp = this->base.substr(i, this->groups[j]);
        if (this->groups[j] + i <= this->base.size() &&
            temp.find('.') == std::string::npos &&
            (this->groups[j] + i == this->base.size() || this->base[i + this->groups[j]] != '#'))
          result += this->arrangements(i + this->groups[j] + 1, j + 1);
      }
      this->memory[key] = result;
      return result;
    }
  };
} // namespace

std::size_t aoc::day12::part1(const std::string &filename)
{
  aoc::vstring input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;

  for (const auto &line : input)
  {
    Record record(line, 1);
    result += record.arrangements(0, 0);
  }

  return result;
}

std::size_t aoc::day12::part2(const std::string &filename)
{
  aoc::vstring input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;
  for (const auto &line : input)
  {
    Record record(line, 5);
    result += record.arrangements(0, 0);
  }

  return result;
}