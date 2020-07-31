//
// Handle a diff sequence
//
#include "diff.hh"

namespace {
  enum class side {
    none = 0,
    left,
    right,
    same
  };

  // Unique ID for side enum
  static const int side_id = std::ios_base::xalloc();

  //display the begin of a line
  void begin_line(std::ostream& stream, side s, unsigned int count = 1) {
    if (s == side::none) return;
    for(;count; count--) {
      switch (s) {
      case side::none:  break;
      case side::left:  stream.put('-'); break;
      case side::right: stream.put('+'); break;
      case side::same:  stream.put(' '); break;
      }
    }
    stream.put(' ');
  }
}

// Unique object
vcard::diff& vcard::diff::stream()
{
  static diff singleton;
  return singleton;
}

// Display the header
std::ostream& vcard::operator<<(std::ostream& stream, const diff::header& h)
{
  stream.iword(side_id) = (long)side::none;
  begin_line(stream, side::left,  3); stream << h._l << std::endl;
  begin_line(stream, side::right, 3); stream << h._r << std::endl;
  return stream;
}

// Manipulators
std::ostream& vcard::diff::left(std::ostream& stream)
{
  stream.iword(side_id) = (long)side::left;
  begin_line(stream, side::left);
  return stream;
}

std::ostream& vcard::diff::right(std::ostream& stream)
{
  stream.iword(side_id) = (long)side::right;
  begin_line(stream, side::right);
  return stream;
}

std::ostream& vcard::diff::same(std::ostream& stream)
{
  stream.iword(side_id) = (long)side::same;
  begin_line(stream, side::same);
  return stream;
}

std::ostream& vcard::diff::endl(std::ostream& stream)
{
  stream.iword(side_id) = (long)side::none;
  stream << std::endl;
  return stream;
}

// Write the stream to effective output
// Handle new lines
int vcard::diff::overflow(int c)
{
  if (c != EOF) std::cout.put(c);
  if (c == '\n') begin_line(std::cout, (side)iword(side_id));

  return c;
}
