#include "aoc/solutions/day17.hpp"

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

#include <iostream>
#include <queue>
#include <unordered_map>

namespace
{
  struct State
  {
    std::size_t hl;
    int         x;
    int         y;
    int         dx;
    int         dy;
    std::size_t n;

    std::string to_string() const { return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(dx) + "," + std::to_string(dy) + "," + std::to_string(n); }
  };

  struct Map
  {
    std::vector<std::vector<std::size_t>> data;

    Map() = default;
    explicit Map(const aoc::vstring &input)
    {
      for (const auto &line : input)
      {
        std::vector<std::size_t> temp;
        for (const auto &character : line)
          temp.emplace_back(std::stoull(std::string(1, character)));
        this->data.emplace_back(temp);
      }
    }

    std::size_t solve(const std::size_t &min_steps, const std::size_t &max_steps)
    {
      int ndx[4] = {0, 1, 0, -1};
      int ndy[4] = {1, 0, -1, 0};

      auto cmp = [](const State &lhs, const State &rhs)
      { return lhs.hl > rhs.hl; };

      const int width  = this->data.front().size();
      const int height = this->data.size();

      std::priority_queue<State, std::vector<State>, decltype(cmp)> pq(cmp);
      std::unordered_map<std::string, bool>                         seen;

      pq.push(State{0, 0, 0, 0, 0, 0});
      while (!pq.empty())
      {
        State state = pq.top();
        pq.pop();
        if (state.x == width - 1 && state.y == height - 1 && state.n >= min_steps)
          return state.hl;

        if (seen.find(state.to_string()) != seen.end()) continue;
        seen[state.to_string()] = true;

        if (state.n < max_steps && !(state.dx == 0 && state.dy == 0))
        {
          int nx = state.x + state.dx;
          int ny = state.y + state.dy;
          if (0 <= nx && nx < width && 0 <= ny && ny < height)
            pq.push(State{state.hl + this->data[ny][nx], nx, ny, state.dx, state.dy, state.n + 1});
        }

        if (state.n >= min_steps || (state.x == 0 && state.y == 0))
          for (std::size_t i = 0; i < 4; ++i)
          {
            if (!(ndx[i] == state.dx && ndy[i] == state.dy) && !(ndx[i] == -state.dx && ndy[i] == -state.dy))
            {
              int nx = state.x + ndx[i];
              int ny = state.y + ndy[i];
              if (0 <= nx && nx < width && 0 <= ny && ny < height)
                pq.push(State{state.hl + this->data[ny][nx], nx, ny, ndx[i], ndy[i], 1});
            }
          }
      }
      return 0;
    }
  };
} // namespace

std::size_t aoc::day17::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map(input);
  return map.solve(1, 3);
}

std::size_t aoc::day17::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map(input);

  return map.solve(4, 10);
}