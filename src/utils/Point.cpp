#include "aoc/utils/Point.hpp"

aoc::Point &aoc::Point::operator=(const Point &other)
{
  this->d_x = other.d_x;
  this->d_y = other.d_y;
  return *this;
}

aoc::Point &aoc::Point::operator=(Point &&other) noexcept
{
  std::swap(this->d_x, other.d_x);
  std::swap(this->d_y, other.d_y);
  return *this;
}

aoc::Point &aoc::Point::operator+=(const std::int64_t &rhs)
{
  this->d_x += rhs;
  this->d_y += rhs;
  return *this;
}

aoc::Point &aoc::Point::operator-=(const std::int64_t &rhs)
{
  this->d_x -= rhs;
  this->d_y -= rhs;
  return *this;
}

aoc::Point &aoc::Point::operator*=(const std::int64_t &rhs)
{
  this->d_x *= rhs;
  this->d_y *= rhs;
  return *this;
}

aoc::Point &aoc::Point::operator/=(const std::int64_t &rhs)
{
  this->d_x /= rhs;
  this->d_y /= rhs;
  return *this;
}

aoc::Point &aoc::Point::operator+=(const Point &rhs)
{
  this->d_x += rhs.d_x;
  this->d_y += rhs.d_y;
  return *this;
}

aoc::Point &aoc::Point::operator-=(const Point &rhs)
{
  this->d_x -= rhs.d_x;
  this->d_y -= rhs.d_y;
  return *this;
}

aoc::Point &aoc::Point::operator*=(const Point &rhs)
{
  this->d_x *= rhs.d_x;
  this->d_y *= rhs.d_y;
  return *this;
}

aoc::Point &aoc::Point::operator/=(const Point &rhs)
{
  this->d_x /= rhs.d_x;
  this->d_y /= rhs.d_y;
  return *this;
}

aoc::Point aoc::Point::operator+(const std::int64_t &rhs) const
{
  Point res = *this;
  res += rhs;
  return res;
}

aoc::Point aoc::Point::operator-(const std::int64_t &rhs) const
{
  Point res = *this;
  res -= rhs;
  return res;
}

aoc::Point aoc::Point::operator*(const std::int64_t &rhs) const
{
  Point res = *this;
  res *= rhs;
  return res;
}

aoc::Point aoc::Point::operator/(const std::int64_t &rhs) const
{
  Point res = *this;
  res /= rhs;
  return res;
}

aoc::Point aoc::Point::operator+(const Point &rhs) const
{
  Point res = *this;
  res += rhs;
  return res;
}

aoc::Point aoc::Point::operator-(const Point &rhs) const
{
  Point res = *this;
  res -= rhs;
  return res;
}

aoc::Point aoc::Point::operator*(const Point &rhs) const
{
  Point res = *this;
  res *= rhs;
  return res;
}

aoc::Point aoc::Point::operator/(const Point &rhs) const
{
  Point res = *this;
  res /= rhs;
  return res;
}
