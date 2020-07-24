//
// Store several vcards
//
#include "error.hh"
#include "address_book.hh"
#include "getline_regardless_eol.hh"
#include <fstream>
#include <string.h>


//
// Create a new address_book from vcard filepath
//
vcard::address_book vcard::address_book::import(std::string filepath)
{
  address_book* book = new address_book();

  std::ifstream fs(filepath);
  if (!fs) throw exception(strize() << "Failed to read file '" << filepath << "': " << strerror(errno));

  // Note: we accept any EOL. The RFC6350 only accept \r\n one.
  int line_nb = 0;
  std::string line;
  std::string field_line;
  bool inside_vard = false;
  vcard card;
  try {
    getline_regardless_eol(fs, field_line);
    while(!getline_regardless_eol(fs, line).eof() || field_line.empty() == false)
    {
      ++line_nb;

      // Unfolding - RFC6350 3.2
      if (line[0] == ' ' || line[0] == '\t') {
        field_line += line.substr(1);
      }
      else {
        // vcard reader
        if (field_line.empty() == false) {   //ignore empty line (shall not happend)
          if (field_line == "BEGIN:VCARD") {
            if (inside_vard) throw exception("Unexpected BEGIN:VCARD after another BEGIN:VCARD.");
            card.clear();
            inside_vard = true;
          } else if (field_line == "END:VCARD") {
            if (inside_vard == false) throw exception("Unexpected END:VCARD outside a VCARD.");
            book->_book.push_back(card);
            inside_vard = false;
          } else if (inside_vard == false) {
            throw exception("Undexpected content outside a VCARD.");
          } else {
            append_field(card, field_line);
          }
        }
        field_line = line;
      }
    }
  } catch (std::exception& e) {
    throw exception(strize() << filepath << ":" << line_nb << " " << e.what());
  }

  return *book;
}

//
// Parse a vcard line and append it to card
//
void vcard::address_book::append_field(vcard& card, std::string line)
{
  size_t pos = line.find(':');
  if (pos == std::string::npos) throw exception("Unexpected line without ':'");

  std::string key = line.substr(0, pos);
  std::string value = line.substr(pos + 1);

  card.insert(key, value);
}


//
// Debug
//
void vcard::address_book::dump() const
{
  for(auto i = _book.begin(); i != _book.end(); i++) {
    i->dump();
  }
}
