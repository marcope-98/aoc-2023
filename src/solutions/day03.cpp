#include "aoc/solutions/day03.hpp"

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

#include <iostream>

namespace
{
  typedef struct
  {
    std::size_t x = 0;
    std::size_t y = 0;
  } Coord;

  typedef struct
  {
    Coord tl;
    Coord br;
  } Rectangle;

  static bool is_digit(const char &character) { return character >= '0' && character <= '9'; }
  static bool is_period(const char &character) { return character == '.'; }
  static bool is_symbol(const char &character) { return !is_digit(character) && !is_period(character); }

  static bool contains(const Rectangle &rect, const Coord &point)
  {
    return (point.x >= rect.tl.x && point.x <= rect.br.x) &&
           (point.y >= rect.tl.y && point.y <= rect.br.y);
  }

  static std::string remove_symbols(const std::string &str)
  {
    std::string out;
    for (const auto &elem : str)
    {
      if (is_digit(elem))
        out += elem;
      else
        out += ".";
    }
    return out;
  }

  static std::vector<Rectangle> get_rectangles(const aoc::vstring &input,
                                               aoc::vstring &      numbers)
  {
    std::vector<Rectangle> out;
    const std::size_t      height = input.size();

    for (std::size_t y = 0; y < height; ++y)
    {
      aoc::vstring ref = aoc::parse::split_by_delimiters(remove_symbols(input[y]), ".");
      std::size_t  pos = 0;
      for (const auto &number : ref)
      {
        Coord tl, br;
        tl.x = (input[y].find(number, pos));
        pos  = tl.x + number.size();
        tl.y = y;
        br.x = tl.x + number.size();
        br.y = y + 1;
        if (tl.x != 0) tl.x -= 1;
        if (tl.y != 0) tl.y -= 1;
        numbers.emplace_back(number);
        out.emplace_back(Rectangle{tl, br});
      }
    }
    return out;
  }

  static std::vector<Coord> get_symbols(const aoc::vstring &input,
                                        aoc::vstring &      symbols)
  {
    std::vector<Coord> out;
    const std::size_t  width  = input[0].size();
    const std::size_t  height = input.size();
    for (std::size_t y = 0; y < height; ++y)
      for (std::size_t x = 0; x < width; ++x)
        if (is_symbol(input[y][x]))
        {
          symbols.emplace_back(std::string(1, input[y][x]));
          out.emplace_back(Coord{x, y});
        }

    return out;
  }
} // namespace

std::size_t aoc::day03::part1(const std::string &filename)
{
  aoc::vstring           input = parse::cvt_file_to_vstring(filename);
  aoc::vstring           numbers, symbols;
  std::vector<Coord>     coords     = get_symbols(input, symbols);
  std::vector<Rectangle> rectangles = get_rectangles(input, numbers);

  std::size_t result = 0;
  for (std::size_t i = 0; i < rectangles.size(); ++i)
    for (const auto &symbol : coords)
      if (contains(rectangles[i], symbol))
      {
        result += std::stoull(numbers[i]);
        break;
      }
  return result;
}

std::size_t aoc::day03::part2(const std::string &filename)
{
  aoc::vstring           input = parse::cvt_file_to_vstring(filename);
  aoc::vstring           numbers, symbols;
  std::vector<Coord>     coords     = get_symbols(input, symbols);
  std::vector<Rectangle> rectangles = get_rectangles(input, numbers);

  std::size_t result = 0;

  for (std::size_t i = 0; i < symbols.size(); ++i)
  {
    if (symbols[i] != "*") continue;
    aoc::vstring adjacents;
    for (std::size_t j = 0; j < rectangles.size(); ++j)
      if (contains(rectangles[j], coords[i]))
        adjacents.emplace_back(numbers[j]);

    if (adjacents.size() == 2)
      result += std::stoull(adjacents[0]) * std::stoull(adjacents[1]);
  }

  return result;
}
