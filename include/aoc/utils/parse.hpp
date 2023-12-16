#ifndef AOC_UTILS_PARSE_HPP_
#define AOC_UTILS_PARSE_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include "aoc/utils/aliases.hpp"

namespace aoc
{
  struct parse
  {
    static std::string              ltrim(std::string s, const char *t = " \t\n\r\f\v");
    static std::string              rtrim(std::string s, const char *t = " \t\n\r\f\v");
    static std::string              trim(std::string s, const char *t = " \t\n\r\f\v");
    static std::string              replace(std::string s, const std::string &from, const char &to);
    static vstring                  cvt_file_to_vstring(const std::string &path);
    static vstring                  split_by_delimiters(std::string line, const std::string &delimiters);
    static vstring                  transpose(const vstring &input);
    static std::vector<std::size_t> find_all(const std::string &str, const char &needle);
    static std::string              concatenate(const vstring &input);
    static vstring                  fliplr(const vstring &input);
    static vstring                  flipud(const vstring &input);
  };
} // namespace aoc
#endif // AOC_UTILS_PARSE_HPP_