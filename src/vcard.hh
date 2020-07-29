//
// Store a vcard data
//
#pragma once
#include <string>
#include <map>

namespace vcard {

  struct vcard
  {
    static bool print_pretty;     // set to true to parse encoding while formatting to stream
    static bool print_folding;    // set to true to fold base64 strings

    typedef std::string                      key_t;
    typedef std::string                      value_t;
    typedef std::pair<const key_t, value_t>  field_t;
    typedef std::multimap<key_t, value_t>    fields_t;

    inline void clear() { _fields.clear(); }

    // Insert an element sorted both by key and value
    void insert(const key_t& key, const value_t& value);

    // Try to build a string to identify the vcard (for display purpose)
    std::string id() const;

    // Display diff with another vcard
    void show_diff(const vcard& right_vcard) const;

    // format to stream
    friend std::ostream& operator<<(std::ostream& os, const field_t& v);
    friend std::ostream& operator<<(std::ostream& os, const vcard& v);

    protected:
    fields_t _fields;
  };

  // Define friend function in vcard namespace
  std::ostream& operator<<(std::ostream& os, const vcard::field_t& v);
  std::ostream& operator<<(std::ostream& os, const vcard& v);
}

