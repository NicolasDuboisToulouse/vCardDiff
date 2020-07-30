//
// Handle a diff sequence
//
#include "diff.hh"

namespace {
  enum class side {
    none = 0,
    left,
    right,
    same,
    header
  };

  static const int size_id = std::ios_base::xalloc();
}


vcard::diff& vcard::diff::stream()
{
  static diff singleton;
  return singleton;
}

std::ostream& vcard::diff::header(std::ostream& stream)
{
  stream << "=== ";
  stream.iword(size_id) = (long)side::header;
  return stream;
}

std::ostream& vcard::diff::left(std::ostream& stream)
{
  stream << "- ";
  stream.iword(size_id) = (long)side::left;
  return stream;
}

std::ostream& vcard::diff::right(std::ostream& stream)
{
  stream << "+ ";
  stream.iword(size_id) = (long)side::right;
  return stream;
}

std::ostream& vcard::diff::same(std::ostream& stream)
{
  stream << "  ";
  stream.iword(size_id) = (long)side::same;
  return stream;
}

std::ostream& vcard::diff::endl(std::ostream& stream)
{
  stream.iword(size_id) = (long)side::none;
  stream << std::endl;
  return stream;
}

int vcard::diff::overflow(int c)
{
  if (c != EOF) {
    std::cout.put(c);
  }

  if (c == '\n') {
    switch ((side)iword(size_id)) {
    case side::left:   std::cout.put('-'); std::cout.put(' '); break;
    case side::right:  std::cout.put('+'); std::cout.put(' '); break;
    case side::same:   std::cout.put(' '); std::cout.put(' '); break;
    case side::header: std::cout << "=== "; break;
    case side::none:  break;
    }
  }

  return c;
}
