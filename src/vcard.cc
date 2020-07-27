#include "error.hh"
#include "string_tools.hh"
#include "vcard.hh"

bool vcard::vcard::pretty_print = false;


// Format one field
std::ostream& vcard::operator<<(std::ostream& os, const vcard::field_t& f)
{
  os << f.first << ":";

  if (vcard::pretty_print == false) return (os << f.second);

  if (find_no_case(f.first, "ENCODING=b")) return (os << "<base64 encoded...>");
  if (find_no_case(f.first, "ENCODING=QUOTED-PRINTABLE")) return (os << unquoted_printable(f.second));

  return (os << f.second);
}

// Format vcard
std::ostream& vcard::operator<<(std::ostream& os, const vcard& v)
{
  os << "BEGIN:VCARD" << std::endl;
  for(auto i = v._fields.begin(); i != v._fields.end(); i++) os << *i << std::endl;
  os << "END:VCARD" << std::endl;
  return os;
}
