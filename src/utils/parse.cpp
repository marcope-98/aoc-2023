#include "aoc/utils/parse.hpp"

#include <cstdint>
#include <fstream>

std::string aoc::parse::ltrim(std::string s, const char *t)
{
  s.erase(0, s.find_first_not_of(t));
  return s;
}

std::string aoc::parse::rtrim(std::string s, const char *t)
{
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

std::string aoc::parse::trim(std::string s, const char *t) { return ltrim(rtrim(s, t), t); }

aoc::vstring aoc::parse::cvt_file_to_vstring(const std::string &path)
{
  std::ifstream file(path);
  aoc::vstring  out;
  std::string   line;
  if (file.is_open())
  {
    while (getline(file, line))
      out.emplace_back(line);
    file.close();
  }
  return out;
}

aoc::vstring aoc::parse::split_by_delimiters(std::string line, const std::string &delimiters)
{
  std::size_t  pos = 0;
  std::string  token;
  aoc::vstring out;

  while ((pos = line.find_first_of(delimiters)) != std::string::npos)
  {
    token = trim(line.substr(0, pos));
    line.erase(0, pos + 1);
    if (!token.empty()) out.emplace_back(token);
  }
  token = trim(line);
  if (!token.empty()) out.emplace_back(token);

  return out;
}
