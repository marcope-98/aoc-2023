#ifndef AOC_UTILS_RANGE_HPP_
#define AOC_UTILS_RANGE_HPP_

#include <cstdint>
#include <vector>

namespace aoc
{
  struct Range
  {
  public:
    Range() = default;
    explicit Range(const std::size_t &point) : d_begin{point}, d_end{point} {}
    Range(const std::size_t &begin, const std::size_t &end) : d_begin{begin}, d_end{end} {}

  public:
    bool operator<(const Range &range) const;
    bool operator>(const Range &range) const;
    bool operator<=(const Range &range) const;
    bool operator>=(const Range &range) const;

    bool operator==(const Range &range) const;
    bool contains(const Range &range) const;

    Range operator+(const Range &range) const;
    Range operator-(const Range &range) const;
    Range operator*(const Range &range) const;
    Range operator/(const Range &range) const;

    Range operator+(const std::size_t &value) const;
    Range operator-(const std::size_t &value) const;
    Range operator*(const std::size_t &value) const;
    Range operator/(const std::size_t &value) const;

    std::size_t  begin() const { return this->d_begin; }
    std::size_t  end() const { return this->d_end; }
    std::size_t &begin() { return this->d_begin; }
    std::size_t &end() { return this->d_end; }

    std::vector<Range> split(const Range &range) const;

  private:
  private:
    std::size_t d_begin{0};
    std::size_t d_end{0};
  };

  inline bool Range::operator<(const Range &range) const { return this->d_end < range.d_begin; }
  inline bool Range::operator>(const Range &range) const { return range.d_end < this->d_begin; }
  inline bool Range::operator<=(const Range &range) const { return this->d_end <= range.d_begin; }
  inline bool Range::operator>=(const Range &range) const { return range.d_end <= this->d_begin; }

  inline bool Range::operator==(const Range &range) const { return this->d_begin == range.d_begin && this->d_end == range.d_end; }

  inline Range Range::operator+(const Range &range) const { return Range(this->d_begin + range.d_begin, this->d_end + range.d_end); }
  inline Range Range::operator-(const Range &range) const { return Range(this->d_begin - range.d_begin, this->d_end - range.d_end); }
  inline Range Range::operator*(const Range &range) const { return Range(this->d_begin * range.d_begin, this->d_end * range.d_end); }
  inline Range Range::operator/(const Range &range) const { return Range(this->d_begin / range.d_begin, this->d_end / range.d_end); }

  inline Range Range::operator+(const std::size_t &value) const { return Range(this->d_begin + value, this->d_end + value); }
  inline Range Range::operator-(const std::size_t &value) const { return Range(this->d_begin - value, this->d_end - value); }
  inline Range Range::operator*(const std::size_t &value) const { return Range(this->d_begin * value, this->d_end * value); }
  inline Range Range::operator/(const std::size_t &value) const { return Range(this->d_begin / value, this->d_end / value); }
} // namespace aoc
#endif // AOC_UTILS_RANGE_HPP_