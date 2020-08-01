//
// stream/string tools
//
#include "string_tools.hh"
#include "error.hh"
#include <algorithm>

//
// Read a line regadless End Of Line (\r \n)
// source: https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf/6089413#6089413
//
std::istream& vcard::getline_regardless_eol(std::istream& is, std::string& str)
{

  str.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(is, true);
  std::streambuf* sb = is.rdbuf();

  for(;;) {
    int c = sb->sbumpc();
    switch (c) {
    case '\n':
      return is;
    case '\r':
      if(sb->sgetc() == '\n')
        sb->sbumpc();
      return is;
    case std::streambuf::traits_type::eof():
      // Also handle the case when the last line has no line ending
      if(str.empty())
        is.setstate(std::ios::eofbit);
      return is;
    default:
      str += (char)c;
    }
  }
}


//
// Look for needle in haystack regadless case
// source: https://stackoverflow.com/questions/3152241/case-insensitive-stdstring-find/19839371#19839371
//
bool vcard::find_no_case(std::string haystack, std::string needle)
{
  auto it = std::search(
    haystack.begin(), haystack.end(),
    needle.begin(),   needle.end(),
    [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
  );
  return (it != haystack.end());
}

// check if vcard key math expected one. (regardless case and attribute)
bool vcard::is_key(const std::string& key, const std::string& expected)
{
  auto ikey = key.begin();
  for (auto iexp = expected.begin();
       iexp != expected.end();
       iexp++, ikey++)
  {
    if (ikey == key.end()) return false;
    if (std::toupper(*iexp) != std::toupper(*ikey)) return false;
  }

  if (ikey != key.end() &&
      *ikey != ':' &&
      *ikey != ';') {
    return false;
  }

  return true;
}



// decode 'quoted-printable' string
std::string vcard::unquoted_printable(std::string quoted)
{
  std::string result;

  for (std::string::size_type pos = 0;
       pos < quoted.length();
       pos++)
  {
    if (quoted[pos] == '=') {
      if (pos + 2 >= quoted.length()) throw exception(strize() << "Unexpected eol while reading quoted-printable '" << quoted << "'");
      auto hex_char = [](char hex) { hex = std::toupper(hex); return (hex > '9') ?  hex - 'A' + 10 : hex - '0'; };
      result += (hex_char(quoted[pos + 1]) << 4) + hex_char(quoted[pos + 2]);
      pos += 2;
    } else {
      result += quoted[pos];
    }
  }

  return result;
}
