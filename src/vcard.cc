#include "error.hh"
#include "string_tools.hh"
#include "vcard.hh"

namespace {
  const std::string::size_type FOLDING_LINE_LENGTH = 74;
}

bool vcard::vcard::print_pretty = false;
bool vcard::vcard::print_folding = false;


// Format one field
std::ostream& vcard::operator<<(std::ostream& os, const vcard::field_t& f)
{
  os << f.first << ":";

  if (find_no_case(f.first, "ENCODING=b")) {
    if (vcard::print_pretty) {
      os <<  "<base64 encoded...>";
    }
    else if (vcard::print_folding) {
      std::string::size_type pos = FOLDING_LINE_LENGTH - (f.first.length() + 1);
      os << f.second.substr(0, pos);
      for (; pos < f.second.length(); pos += FOLDING_LINE_LENGTH - 1) {
        os << std::endl << ' ';
        os << f.second.substr(pos, FOLDING_LINE_LENGTH - 1);
      }
    }
    else {
      os << f.second;
    }
  }

  else if (vcard::print_pretty == true && find_no_case(f.first, "ENCODING=QUOTED-PRINTABLE")) {
    os << unquoted_printable(f.second);
  }

  else {
    os << f.second;
  }

  return os;
}


// Format vcard
std::ostream& vcard::operator<<(std::ostream& os, const vcard& v)
{
  os << "BEGIN:VCARD" << std::endl;
  for(auto i = v._fields.begin(); i != v._fields.end(); i++) os << *i << std::endl;
  os << "END:VCARD" << std::endl;
  return os;
}
