#include "aoc/solutions/day15.hpp"

#include <algorithm>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  std::size_t hash(const std::string &input)
  {
    std::size_t result = 0;
    for (const auto &character : input)
    {
      result += std::size_t(character);
      result *= 17;
      result %= 256;
    }
    return result;
  }

  struct Lens
  {
    std::string hash;
    std::size_t focal_length;
    bool        operator==(const Lens &other) const { return this->hash == other.hash; }
  };

  struct Boxes
  {
    std::vector<Lens> boxes[256];

    Boxes() = default;
    void solve(std::string str)
    {
      if (str.back() == '-')
      {
        str.pop_back();
        std::size_t key = hash(str);
        for (auto it = this->boxes[key].begin(); it != this->boxes[key].end();)
          if (it->hash == str)
          {
            it = this->boxes[key].erase(it);
            return;
          }
          else
            it++;
      }
      else
      {
        aoc::vstring temp = aoc::parse::split_by_delimiters(str, "=");
        std::size_t  key  = hash(temp.front());
        auto         it   = std::find(this->boxes[key].begin(), this->boxes[key].end(), Lens{temp.front(), 0});
        if (it == this->boxes[key].end())
          this->boxes[key].emplace_back(Lens{temp.front(), std::stoull(temp.back())});
        else
          it->focal_length = std::stoull(temp.back());
      }
    }

    std::size_t focusing_power() const
    {
      std::size_t result = 0;
      for (std::size_t i = 0; i < 256; ++i)
        for (std::size_t j = 0; j < this->boxes[i].size(); ++j)
          result += (i + 1) * (j + 1) * (this->boxes[i][j].focal_length);
      return result;
    }
  };
} // namespace

std::size_t aoc::day15::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  input              = aoc::parse::split_by_delimiters(input.front(), ",");

  std::size_t result = 0;
  for (const auto &line : input)
    result += hash(line);

  return result;
}

std::size_t aoc::day15::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  input              = aoc::parse::split_by_delimiters(input.front(), ",");
  Boxes boxes;
  for (const auto &line : input)
    boxes.solve(line);

  return boxes.focusing_power();
}