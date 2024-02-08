#include "aoc/solutions/day22.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  struct Brick : public std::vector<std::size_t>
  {
    explicit Brick(const aoc::vstring &input)
    {
      this->reserve(input.size());
      for (const auto &coord : input)
        this->emplace_back(std::stoull(coord));
    }
    std::string to_string() const
    {
      return std::to_string(this->at(0)) + "," +
             std::to_string(this->at(1)) + "," +
             std::to_string(this->at(2)) + "~" +
             std::to_string(this->at(3)) + "," +
             std::to_string(this->at(4)) + "," +
             std::to_string(this->at(5));
    }
  };

  bool overlaps(const Brick &lhs, const Brick &rhs)
  {
    return std::max(lhs[0], rhs[0]) <= std::min(lhs[3], rhs[3]) &&
           std::max(lhs[1], rhs[1]) <= std::min(lhs[4], rhs[4]);
  }

  std::vector<Brick> get_bricks(const aoc::vstring &input)
  {
    std::vector<Brick> bricks;
    bricks.reserve(input.size());
    for (const auto &line : input)
      bricks.emplace_back(Brick(aoc::parse::split_by_delimiters(line, ",~")));
    return bricks;
  }

  void collapse(std::vector<Brick> &bricks)
  {
    std::sort(bricks.begin(), bricks.end(), [](const Brick &lhs, const Brick &rhs)
              { return lhs[2] < rhs[2]; });

    for (std::size_t i = 0; i < bricks.size(); ++i)
    {
      std::size_t max_z = 1;
      for (std::size_t j = 0; j < i; ++j)
        if (overlaps(bricks[i], bricks[j]))
          max_z = std::max(max_z, bricks[j][5] + 1);
      bricks[i][5] -= bricks[i][2] - max_z;
      bricks[i][2] = max_z;
    }

    std::sort(bricks.begin(), bricks.end(), [](const Brick &lhs, const Brick &rhs)
              { return lhs[2] < rhs[2]; });
  }

  bool all_supports_are_falling(const std::unordered_set<std::size_t> &falling, const std::unordered_set<std::size_t> &supporting)
  {
    for (const auto &elem : supporting)
      if (falling.find(elem) == falling.end())
        return false;
    return true;
  }

  bool deletable(const std::unordered_set<std::size_t> &k_supports_v, const std::vector<std::unordered_set<std::size_t>> &v_supports_k)
  {
    for (const auto &elem : k_supports_v)
      if (v_supports_k[elem].size() < 2) return false;
    return true;
  }

} // namespace

std::size_t aoc::day22::part1(const std::string &filename)
{
  aoc::vstring       input  = aoc::parse::cvt_file_to_vstring(filename);
  std::vector<Brick> bricks = get_bricks(input);
  collapse(bricks);

  std::vector<std::unordered_set<std::size_t>> k_supports_v(bricks.size());
  std::vector<std::unordered_set<std::size_t>> v_supports_k(bricks.size());

  for (std::size_t j = 0; j < bricks.size(); ++j)
    for (std::size_t i = 0; i < j; ++i)
      if (overlaps(bricks[i], bricks[j]) && bricks[j][2] == bricks[i][5] + 1)
      {
        k_supports_v[i].insert(j);
        v_supports_k[j].insert(i);
      }

  std::size_t result = 0;
  for (std::size_t i = 0; i < bricks.size(); ++i)
    if (deletable(k_supports_v[i], v_supports_k))
      result++;
  return result;
}

std::size_t aoc::day22::part2(const std::string &filename)
{
  aoc::vstring       input  = aoc::parse::cvt_file_to_vstring(filename);
  std::vector<Brick> bricks = get_bricks(input);

  collapse(bricks);

  std::vector<std::unordered_set<std::size_t>> k_supports_v(bricks.size());
  std::vector<std::unordered_set<std::size_t>> v_supports_k(bricks.size());

  for (std::size_t j = 0; j < bricks.size(); ++j)
    for (std::size_t i = 0; i < j; ++i)
      if (overlaps(bricks[i], bricks[j]) && bricks[j][2] == bricks[i][5] + 1)
      {
        k_supports_v[i].insert(j);
        v_supports_k[j].insert(i);
      }

  std::size_t result = 0;
  for (std::size_t i = 0; i < bricks.size(); ++i)
  {
    if (!deletable(k_supports_v[i], v_supports_k))
    {
      std::queue<std::size_t>         candidates;
      std::unordered_set<std::size_t> falling;
      for (const auto &supported_brick : k_supports_v[i])
        candidates.push(supported_brick);
      falling.insert(i);

      while (!candidates.empty())
      {
        std::size_t brick = candidates.front();
        candidates.pop();

        if (falling.find(brick) == falling.end() && all_supports_are_falling(falling, v_supports_k[brick]))
        {
          result++;
          falling.insert(brick);
          for (const auto &supported_brick : k_supports_v[brick])
            candidates.push(supported_brick);
        }
      }
    }
  }

  return result;
}