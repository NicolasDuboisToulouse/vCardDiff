//
// Store several vcards
//
#pragma once
#include "vcard.hh"
#include <list>

namespace vcard {

  struct address_book
  {
    // Create an address_book from a vcard file
    // Throw an exception on unrecoverable parse error
    static address_book import(std::string filepath);

    // Debug
    void dump() const;

  protected:
    static void append_field(vcard& card, std::string field_line);

    typedef std::list<vcard> book_t;
    book_t _book;
  };

}

