#include "error.hh"
#include "address_book.hh"

int main(int argc, char** argv)
{
  std::string sofware(argv[0]);
  size_t last = sofware.find_last_of("/\\");
  if (last != std::string::npos) sofware = sofware.substr(last + 1);

  if (argc != 2 || argv[1][0] == '-') {
    ERROR("USAGE: " << sofware << " <file.vcf>");
    return 1;
  }

  vcard::address_book my_book = vcard::address_book::import(argv[1]);

  my_book.dump();
  return 0;
}
