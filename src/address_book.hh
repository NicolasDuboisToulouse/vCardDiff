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

    // Return the path of the file used to build address_book.
    // Will be empty if not built throw import() function.
    std::string filepath() { return _filepath; }

    // Return the first card (throw an error if address bool is empty)
    const vcard& first();

    // Format to stream
    friend std::ostream& operator<<(std::ostream& os, const address_book& v);

  protected:
    typedef std::list<vcard> book_t;
    std::string _filepath;
    book_t      _book;
  };

  // Define friend function in vcard namespace
  std::ostream& operator<<(std::ostream& os, const address_book& ab);
}

