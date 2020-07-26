#include "error.hh"
#include "vcard.hh"

// Format one field
std::ostream& vcard::operator<<(std::ostream& os, const vcard::field_t& f)
{
  return (os << f.first << ":" << f.second);
}

// Format vcard
std::ostream& vcard::operator<<(std::ostream& os, const vcard& v)
{
  os << "BEGIN:VCARD" << std::endl;
  for(auto i = v._fields.begin(); i != v._fields.end(); i++) os << *i << std::endl;
  os << "END:VCARD" << std::endl;
  return os;
}
