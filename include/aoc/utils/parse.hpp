#ifndef AOC_PARSE_HPP_
#define AOC_PARSE_HPP_

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace aoc
{
  struct parse
  {
    static std::vector<std::string> cvt_file_to_vstring(const std::string &path)
    {
      std::ifstream            file(path);
      std::vector<std::string> out{};
      std::string              line{};
      while (getline(file, line))
        out.emplace_back(line);
      file.close();
      return out;
    }

    static bool        contains(const std::string &source, const std::string &pattern) { return source.find(pattern) != std::string::npos; }
    static std::size_t find_character(const std::string &line, const std::string &character) { return line.find(character); }

    static std::vector<std::string> split_by_delimiter(const std::string &line, const std::string &delimiter)
    {
      std::string              temp = line;
      std::vector<std::string> out;
      std::size_t              offset;
      for (;;)
      {
        offset = find_character(temp, delimiter);
        if (offset == std::string::npos) break;
        out.emplace_back(temp.substr(0, offset));
        temp = temp.substr(offset + 1);
      }
      out.emplace_back(temp);
      return out;
    }
  };
} // namespace aoc
#endif // AOC_PARSE_HPP_