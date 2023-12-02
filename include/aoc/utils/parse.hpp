#ifndef AOC_UTILS_PARSE_HPP_
#define AOC_UTILS_PARSE_HPP_

#include <string>

#include "aoc/utils/aliases.hpp"

namespace aoc
{
  struct parse
  {
    static std::string ltrim(std::string s, const char *t = " \t\n\r\f\v");
    static std::string rtrim(std::string s, const char *t = " \t\n\r\f\v");
    static std::string trim(std::string s, const char *t = " \t\n\r\f\v");
    static vstring     cvt_file_to_vstring(const std::string &path);
    static vstring     split_by_delimiters(std::string line, const std::string &delimiters);
  };
} // namespace aoc
#endif // AOC_UTILS_PARSE_HPP_