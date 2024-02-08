#include "aoc/solutions/day21.hpp"

#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_set>

#include "aoc/utils/Point.hpp"
#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  struct Polynomial
  {
    double a, b, c;

    Polynomial(const std::vector<double> &x, const std::vector<double> &y)
    {
      this->a = (y[0] - 2.f * y[1] + y[2]) / (x[0] * x[0] - 2.f * x[1] * x[1] + x[2] * x[2]);
      this->b = (y[2] - y[1] - this->a * x[2] * x[2] + this->a * x[1] * x[1]) / (x[2] - x[1]);
      this->c = y[2] - this->a * x[2] * x[2] - this->b * x[2];
    }

    std::size_t solve(const double &n) const { return round(this->a * n * n + this->b * n + this->c); }
  };

  struct State
  {
    aoc::Point  point;
    std::size_t steps;
  };

  struct Map
  {
    aoc::Point   start;
    aoc::vstring data;

    Map() = default;
    explicit Map(const aoc::vstring &input) : data(input)
    {
      for (std::size_t y = 0; y < this->data.size(); ++y)
        for (std::size_t x = 0; x < this->data[y].size(); ++x)
          if (this->data[y][x] == 'S')
            this->start = aoc::Point(x, y);
    }

    std::size_t width() const { return this->data.front().size(); }
    std::size_t height() const { return this->data.size(); }
    bool        in_bound(const aoc::Point &point) const { return 0 <= point.x() && point.x() < (std::int64_t)this->width() && 0 <= point.y() && point.y() < (std::int64_t)this->height(); }
    char        at(aoc::Point point) const
    {
      point.x() %= (std::int64_t)this->width();
      point.x() += std::int64_t(point.x() < 0) * (std::int64_t)this->width();
      point.y() %= (std::int64_t)this->height();
      point.y() += std::int64_t(point.y() < 0) * (std::int64_t)this->height();
      return this->data[point.y()][point.x()];
    }

    std::size_t count(const std::size_t &steps, const bool &part1 = true) const
    {
      aoc::Point moves[4] = {aoc::Point(-1, 0), aoc::Point(1, 0), aoc::Point(0, -1), aoc::Point(0, 1)};

      std::unordered_set<std::string> seen;
      std::queue<State>               q;
      std::size_t                     result = 0;
      seen.insert(this->start.to_string());
      q.push(State{this->start, steps});

      while (!q.empty())
      {
        State state = q.front();
        q.pop();
        if (state.steps % 2 == 0) result++;
        if (state.steps == 0) return result + q.size();
        for (std::size_t i = 0; i < 4; ++i)
        {
          aoc::Point point = state.point + moves[i];
          if ((!this->in_bound(point) && part1) || this->at(point) == '#' || seen.find(point.to_string()) != seen.end()) continue;
          seen.insert(point.to_string());
          q.push(State{point, state.steps - 1});
        }
      }
      return result;
    }

    std::size_t solve(const std::size_t &steps, const bool &part1 = true)
    {
      std::size_t starting_i = 4;
      if (steps < 2 * starting_i * this->width()) return this->count(steps, part1);
      std::size_t remainder = steps % this->width();

      std::vector<double> x, y;

      for (std::size_t i = starting_i; i < starting_i + 3; ++i)
      {
        std::size_t n_steps = this->width() * i + remainder;
        x.emplace_back((double)(n_steps));
        y.emplace_back((double)(this->count(n_steps, false)));
      }

      Polynomial polynomial(x, y);
      return polynomial.solve(steps);
    }
  };

} // namespace

std::size_t aoc::day21::part1(const std::string &filename, const std::size_t &steps)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map(input);
  return map.solve(steps);
}

std::size_t aoc::day21::part2(const std::string &filename, const std::size_t &steps)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Map          map(input);
  return map.solve(steps, false);
}
