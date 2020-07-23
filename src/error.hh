//
// Error managment and debug stuff
//
#pragma once
#include <string>
#include <iostream>
#include <sstream>

namespace vcard {

  // Basic messages wrappers
# define _VCARD_LOGSTREAM std::cerr
# define ERROR(m) do { _VCARD_LOGSTREAM << m << std::endl; } while (0)
# define DEBUG(m) do { _VCARD_LOGSTREAM << __FILE__ << ":" << __LINE__ << " " << m << std::endl; } while (0)

  // Simple string exception
  struct exception : public std::exception
  {
    explicit exception(const std::string& m) : _m(m) {}
    virtual const char* what() const noexcept override { return _m.c_str(); }
    virtual ~exception() noexcept override {}
  private:
    std::string _m;
  };

  // convert stream to string. Samples:
  // std::string foo = strize() << "Value: " << 42;
  // throw exception(strize() << "Value: " << 42);
  struct strize {
    template <typename T> strize& operator<<(T obj) { _ss << obj; return *this; }
    operator std::string() const noexcept { return _ss.str(); }
  private:
    std::stringstream _ss;
  };

}
