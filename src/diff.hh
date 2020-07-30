//
// Handle a diff sequence
//
#pragma once
#include <iostream>

namespace vcard
{
  //
  // diff stream that handle std::endl inside a left/right sequece.
  // usage: diff::stream() << diff:left << "left squequence" << std::endl << "left continued" << diff::endl;
  //
  struct diff : protected std::ostream, protected std::streambuf
  {
    using std::ostream::operator<<;
    static diff& stream();

    static std::ostream& header(std::ostream& stream);
    static std::ostream& left(std::ostream& stream);
    static std::ostream& right(std::ostream& stream);
    static std::ostream& same(std::ostream& stream);
    static std::ostream& endl(std::ostream& stream);

  protected:
    diff() : std::ostream(this) {}
    int overflow(int c) override;
  };

}
