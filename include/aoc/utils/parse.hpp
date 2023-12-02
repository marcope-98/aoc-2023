#ifndef AOC_UTILS_PARSE_HPP_
#define AOC_UTILS_PARSE_HPP_

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace aoc
{
  struct parse
  {
    static std::string ltrim(std::string s, const char *t = " \t\n\r\f\v")
    {
      s.erase(0, s.find_first_not_of(t));
      return s;
    }

    static std::string rtrim(std::string s, const char *t = " \t\n\r\f\v")
    {
      s.erase(s.find_last_not_of(t) + 1);
      return s;
    }

    static std::string trim(std::string s, const char *t = " \t\n\r\f\v")
    {
      return ltrim(rtrim(s, t), t);
    }

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

    static std::vector<std::string> split_by_delimiter(std::string line, const std::string &delimiter)
    {
      std::size_t              pos = 0;
      std::string              token;
      std::vector<std::string> out;
      while ((pos = line.find(delimiter)) != std::string::npos)
      {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        out.emplace_back(trim(token));
      }
      out.emplace_back(trim(line));
      return out;
    }
  };
} // namespace aoc
#endif // AOC_UTILS_PARSE_HPP_