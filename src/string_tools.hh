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
}
