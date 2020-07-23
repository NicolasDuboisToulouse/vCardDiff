#include "error.hh"
#include "vcard.hh"


void vcard::vcard::dump() const
{
  DEBUG("BEGIN::VCARD");
  for(auto i = _fields.begin(); i != _fields.end(); i++) {
    DEBUG(i->first << ":" << i->second);
  }
  DEBUG("END::VCARD");
}
