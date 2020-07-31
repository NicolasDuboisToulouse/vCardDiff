//
// Handle a diff sequence
//
#pragma once
#include <iostream>

namespace vcard
{
  // Diplay diff 'lines' with appropriate prefix.
  // diff::left, diff::right, diff::same begin a line. diff::endl end a line.
  // new lines (std::endl) are supported in diff 'lines'.
  struct diff : public std::ostream, protected std::streambuf
  {
    static diff& stream();

    // Display diff header.
    struct header {
      std::string _l; std::string _r;
      header(std::string l, std::string r) : _l(l), _r(r) {}
    };

    // Start a diff line
    static std::ostream& left(std::ostream& stream);
    static std::ostream& right(std::ostream& stream);
    static std::ostream& same(std::ostream& stream);

    // End a diff line
    static std::ostream& endl(std::ostream& stream);

  protected:
    diff() : std::ostream(this) {}
    int overflow(int c) override;
  };

  std::ostream& operator<<(std::ostream& os, const diff::header& h);

}
