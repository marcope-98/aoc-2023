#ifndef AOC_UTILS_POLYGON_HPP_
#define AOC_UTILS_POLYGON_HPP_

#include <cstdint>
#include <vector>

#include "aoc/utils/Point.hpp"

namespace aoc
{
  struct Polygon : public std::vector<Point>
  {
  private:
    std::int64_t finite_difference() const
    {
      std::int64_t res = 0;
      for (std::size_t i = 0; i < this->size() - 1; ++i)
        res += (this->at(i) * this->at(i + 1).invert()).sub();
      res += (this->back() * this->front().invert()).sub();
      return res;
    }

  public:
    bool is_ccw() const { return this->finite_difference() > 0; }

    std::int64_t perimeter() const
    {
      std::int64_t res = 0;
      for (std::size_t i = 0; i < this->size() - 1; ++i)
        res += (this->at(i) - this->at(i + 1)).abs().sum();
      res += (this->front() - this->back()).abs().sum();
      return res;
    }

    std::int64_t area() const
    {
      std::int64_t fd = this->finite_difference();
      return fd > 0 ? fd / 2 : -fd / 2;
    }
  };
} // namespace aoc

#endif // AOC_UTILS_POLYGON_HPP_