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

    // format to stream
    friend std::ostream& operator<<(std::ostream& os, const address_book& v);

  protected:
    typedef std::list<vcard> book_t;
    book_t _book;
  };

  // Define friend function in vcard namespace
  std::ostream& operator<<(std::ostream& os, const address_book& ab);
}

