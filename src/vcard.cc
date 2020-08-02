#include "error.hh"
#include "string_tools.hh"
#include "vcard.hh"
#include "diff.hh"
#include <algorithm>
#include <list>


// Insert an element sorted both by key and value
void vcard::vcard::insert(const key_t& key, const value_t& value)
{
  auto same_key = _fields.equal_range(key);
  for (auto isame_key = same_key.first; isame_key != same_key.second; isame_key++) {
    if (value < isame_key->second) {
      _fields.emplace_hint(isame_key, key, value);
      return;
    }
  }
  _fields.emplace(key, value);
}


// Identify vcard
std::string vcard::vcard::id() const
{
  std::string result;

  std::list<std::string> keys = { "FN", "N", "NICKNAME" };
  for (auto ik = keys.begin(); ik != keys.end(); ik++) {
    fields_t::const_iterator ifield = _fields.find(*ik);
    if (ifield != _fields.end()) {
      result = ifield->second;
      std::replace(result.begin(), result.end(), ';', ' ');
      break;
    }
  }

  fields_t::const_iterator ifield = _fields.find("UID");
  if (ifield != _fields.end()) {
    if (result.empty() == false) result += " UID:";
    result += ifield->second;
  }

  if (result.empty() == false) return result;
  return "???";
}


// Return all the UIDs. May be empty.
vcard::vcard::values_t vcard::vcard::uids() const
{
  values_t result;
  for (auto ifield = _fields.begin(); ifield != _fields.end(); ifield++) {
    if (is_key(ifield->first, "UID")) result.push_back(ifield->second);
  }
  return result;
}

// Return strings that may represent full name of the card. May be empty.
vcard::vcard::values_t vcard::vcard::names() const
{
  values_t result;
  const std::list<std::string> name_keys = { "FN", "N", "NICKNAME" };
  for (auto ifield = _fields.begin(); ifield != _fields.end(); ifield++) {
    for (auto key : name_keys) {
      if (is_key(ifield->first, key)) {
        std::string name = format_name(ifield->second, find_no_case(ifield->first, "ENCODING=QUOTED-PRINTABLE"));
        result.push_back(name);
      }
    }
  }
  return result;
}

// Return all the TELs. May be empty.
vcard::vcard::values_t vcard::vcard::tels() const
{
  values_t result;
  for (auto ifield = _fields.begin(); ifield != _fields.end(); ifield++) {
    if (is_key(ifield->first, "TEL")) result.push_back(format_tel(ifield->second));
  }
  return result;
}



// Display the diff
void vcard::vcard::show_diff(const vcard& right_vcard) const
{
  diff::stream() << diff::header(id(), right_vcard.id());

  const fields_t& left = _fields;
  const fields_t& right = right_vcard._fields;

  fields_t::const_iterator ileft = left.begin();
  fields_t::const_iterator iright = right.begin();
  while (ileft != left.end() && iright != right.end()) {
    if (*ileft < *iright) {
      diff::stream() << diff::left << *ileft << diff::endl;
      ileft++;
    } else {
      if ( *iright < *ileft) {
        diff::stream() << diff::right << *iright << diff::endl;
      } else {
        diff::stream() << diff::same << *ileft << diff::endl;
        ileft++;
      }
      iright++;
    }
  }
  for (; ileft != left.end(); ileft++) diff::stream() << diff::left << *ileft << diff::endl;
  for (; iright != right.end(); iright++) diff::stream() << diff::right << *iright << diff::endl;
}


// Formatting configuration
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
