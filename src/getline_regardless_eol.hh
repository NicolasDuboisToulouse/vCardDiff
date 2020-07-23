//
// like std::getline but don't care about eol (\r\n)
//
#include <istream>

namespace vcard {
  std::istream& getline_regardless_eol(std::istream& is, std::string& str);
}
