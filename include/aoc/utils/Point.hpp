#ifndef AOC_UTILS_POINT_HPP_
#define AOC_UTILS_POINT_HPP_

#include <cstdint>
#include <string>
#include <utility>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace aoc
{
  class Point
  {
  public:
    Point() = default;
    explicit Point(const std::string &key)
    {
      aoc::vstring temp = aoc::parse::split_by_delimiters(key, ",");
      this->d_x         = std::stoi(temp.front());
      this->d_y         = std::stoi(temp.back());
    }

    Point(const std::int64_t &x, const std::int64_t &y) : d_x{x}, d_y{y} {}
    Point(const Point &other) { *this = other; }
    Point(Point &&other) noexcept { *this = std::move(other); }
    ~Point() = default;

    Point &operator=(const Point &other);
    Point &operator=(Point &&other) noexcept;

  public:
    bool operator==(const Point &rhs) const { return this->d_x == rhs.d_x && this->d_y == rhs.d_y; }

    Point &operator+=(const std::int64_t &rhs);
    Point &operator-=(const std::int64_t &rhs);
    Point &operator*=(const std::int64_t &rhs);
    Point &operator/=(const std::int64_t &rhs);

    Point &operator+=(const Point &rhs);
    Point &operator-=(const Point &rhs);
    Point &operator*=(const Point &rhs);
    Point &operator/=(const Point &rhs);

    Point operator+(const std::int64_t &rhs) const;
    Point operator-(const std::int64_t &rhs) const;
    Point operator*(const std::int64_t &rhs) const;
    Point operator/(const std::int64_t &rhs) const;

    Point operator+(const Point &rhs) const;
    Point operator-(const Point &rhs) const;
    Point operator*(const Point &rhs) const;
    Point operator/(const Point &rhs) const;

    std::int64_t  x() const { return this->d_x; }
    std::int64_t  y() const { return this->d_y; }
    std::int64_t &x() { return this->d_x; }
    std::int64_t &y() { return this->d_y; }

    bool in_range(const Point &lower, const Point &upper) const
    {
      return lower.d_x <= this->d_x && this->d_x <= upper.d_x &&
             lower.d_y <= this->d_y && this->d_y <= upper.d_y;
    }

    Point abs() const
    {
      Point res = *this;
      if (this->d_x < 0) res.d_x = -this->d_x;
      if (this->d_y < 0) res.d_y = -this->d_y;
      return res;
    }

    std::int64_t sum() const { return this->d_x + this->d_y; }
    std::int64_t sub() const { return this->d_x - this->d_y; }
    Point        invert() const { return Point(this->d_y, this->d_x); }
    std::string  to_string() const { return std::to_string(this->d_x) + "," + std::to_string(this->d_y); }

  private:
  private:
    std::int64_t d_x{0};
    std::int64_t d_y{0};
  };

} // namespace aoc

#endif // AOC_UTILS_POINT_HPP_