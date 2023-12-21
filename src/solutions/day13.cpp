#include "aoc/solutions/day13.hpp"

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"
namespace
{
  std::size_t set_bits(std::size_t x)
  {
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
    x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
    return x;
  }

  struct Pattern
  {
    std::vector<std::size_t> data;

    Pattern() = default;
    explicit Pattern(const aoc::vstring &input)
    {
      this->data.reserve(input.size());
      for (const auto &line : input)
      {
        std::size_t temp = 0;
        for (const auto &character : line)
        {
          temp <<= 1u;
          temp |= character == '#' ? 1 : 0;
        }
        this->data.emplace_back(temp);
      }
    }

    std::vector<std::size_t> get_pairs() const
    {
      std::vector<std::size_t> res;
      for (std::size_t i = 0; i < this->data.size() - 1; ++i)
        if (this->data[i] == this->data[i + 1])
          res.emplace_back(i);
      return res;
    }

    std::vector<std::size_t> reflection_lines_candidates() const
    {
      std::vector<std::size_t> pairs = this->get_pairs();
      // remove reflection from pair if exists
      for (auto it = pairs.begin(); it != pairs.end();)
        if (is_reflection(*it))
          it = pairs.erase(it);
        else
          ++it;
      // find possible reflection lines (smudge is on the reflection line)
      for (std::size_t i = 0; i < this->data.size() - 1; ++i)
        if (set_bits(this->data[i] ^ this->data[i + 1]) == 1)
          pairs.emplace_back(i);

      return pairs;
    }

    std::size_t solve_smudge()
    {
      std::vector<std::size_t> pairs = this->reflection_lines_candidates();

      for (const auto &pair : pairs)
      {
        if (this->data[pair] == this->data[pair + 1])
        {
          // smudge not on reflection line
          std::size_t begin        = pair;
          std::size_t end          = pair + 1;
          std::size_t set_bits_sum = 0;

          do
          {
            set_bits_sum += set_bits(this->data[--begin] ^ this->data[++end]);
          } while (begin != 0 && end != this->data.size() - 1);
          if (set_bits_sum == 1) return pair + 1;
        }
        else
        {
          // smudge in reflection line
          std::size_t mask = this->data[pair] ^ this->data[pair + 1];
          this->data[pair] ^= mask;
          if (is_reflection(pair)) return pair + 1;
          this->data[pair] ^= mask;
        }
      }
      return 0;
    }

    bool is_reflection(const std::size_t &index) const
    {
      std::size_t begin = index;
      std::size_t end   = index + 1;
      if (end == this->data.size() - 1 || begin == 0) return true;
      // begin == end by default
      do
      {
        if (this->data[--begin] != this->data[++end])
          return false;
      } while (begin != 0 && end != this->data.size() - 1);
      return true;
    }

    std::size_t solve() const
    {
      std::vector<std::size_t> pairs = this->get_pairs();
      for (const auto &pair : pairs)
      {
        if (this->is_reflection(pair))
          return pair + 1;
      }
      return 0;
    }
  };

  aoc::vstring get_pattern(aoc::vstring &input)
  {
    auto         empty_line_it = input.end();
    aoc::vstring res;
    for (auto it = input.begin(); it != input.end(); ++it)
      if (it->empty())
      {
        empty_line_it = it + 1;
        break;
      }
      else
        res.emplace_back(*it);

    input.erase(input.begin(), empty_line_it);
    return res;
  }
} // namespace

std::size_t aoc::day13::part1(const std::string &filename)
{
  aoc::vstring input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;

  while (!input.empty())
  {
    aoc::vstring temp = get_pattern(input);
    Pattern      vpattern(aoc::parse::transpose(temp));
    Pattern      hpattern(temp);
    result += vpattern.solve() + 100 * hpattern.solve();
  }

  return result;
}

std::size_t aoc::day13::part2(const std::string &filename)
{
  aoc::vstring input  = aoc::parse::cvt_file_to_vstring(filename);
  std::size_t  result = 0;

  while (!input.empty())
  {
    aoc::vstring temp = get_pattern(input);
    Pattern      vpattern(aoc::parse::transpose(temp));
    Pattern      hpattern(temp);
    result += vpattern.solve_smudge() + 100 * hpattern.solve_smudge();
  }

  return result;
}
