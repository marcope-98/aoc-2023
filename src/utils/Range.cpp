#include "aoc/utils/Range.hpp"

#include <algorithm>

bool aoc::Range::contains(const Range &range) const { return this->d_begin <= range.d_begin && range.d_end <= this->d_end; }

std::vector<aoc::Range> aoc::Range::split(const Range &range) const
{
  std::vector<Range> out;
  if (*this < range || *this > range || range.contains(*this))
  {
    out.emplace_back(*this);
    return out;
  }

  std::vector<std::size_t> temp = {this->d_begin, this->d_end};
  if (this->d_begin < range.d_begin)
  {
    temp.emplace_back(range.d_begin - 1);
    temp.emplace_back(range.d_begin);
  }

  if (this->d_end > range.d_end)
  {
    temp.emplace_back(range.d_end);
    temp.emplace_back(range.d_end + 1);
  }
  std::sort(temp.begin(), temp.end());
  for (std::size_t i = 0; i < temp.size() - 1; i += 2)
    out.emplace_back(Range(temp[i], temp[i + 1]));
  return out;
}