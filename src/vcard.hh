//
// Store a vcard data
//
#pragma once
#include <string>
#include <unordered_map>

namespace vcard {

  struct vcard
  {
    typedef std::string                         key_t;
    typedef std::string                         value_t;
    typedef std::pair<const key_t, value_t>     field_t;
    typedef std::unordered_map<key_t, value_t>  fields_t;

    inline void clear() { _fields.clear(); }
    inline void insert(const key_t& key, const value_t& value) { _fields.insert(field_t(key, value)); }

    // Debug
    void dump() const;

    protected:
    fields_t _fields;
  };

}

