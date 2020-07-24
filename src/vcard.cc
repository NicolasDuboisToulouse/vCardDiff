#include "error.hh"
#include "vcard.hh"


void vcard::vcard::dump() const
{
  MSG("BEGIN:VCARD");
  for(auto i = _fields.begin(); i != _fields.end(); i++) {
    MSG(i->first << ":" << i->second);
  }
  MSG("END:VCARD");
}
