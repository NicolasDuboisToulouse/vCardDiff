//
// stream/string tools
//
#pragma once
#include <istream>

namespace vcard {
  // Read a line regadless End Of Line (\r \n)
  std::istream& getline_regardless_eol(std::istream& is, std::string& str);

  // Look for needle in haystack regadless case
  bool find_no_case(std::string haystack, std::string needle);

  // check if vcard key math expected one. (regardless case and attribute)
  bool is_key(const std::string& key, const std::string& expected);

  // Decode 'quoted-printable' string (do not handle encoding)
  std::string unquoted_printable(std::string quoted);

  // Remove useless spaces and ';' from name. Optionally decode 'quoted-printable'.
  std::string format_name(std::string name, bool unquote = false);

  // Convert a tel number to local number-only tel number
  std::string format_tel(std::string tel);
}
