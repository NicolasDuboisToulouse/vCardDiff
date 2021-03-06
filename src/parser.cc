#include "error.hh"
#include "address_book.hh"

void usage(std::string software)
{
  MSG("USAGE: " << software << " [-p|-f] <file.vcf>");
  MSG("  Test the parser: Parse given file and print it.");
  MSG("");
  MSG("  -p          Pretty print. Parse quoted-printable strings and some other stuff.");
  MSG("  -f          Folding print. Fold base64-encoded string (not impmlemented for other strings).");
  MSG("  <file.vcf>  File to parse.");
}


int main(int argc, char** argv)
{
  std::string sofware(argv[0]);
  size_t last = sofware.find_last_of("/\\");
  if (last != std::string::npos) sofware = sofware.substr(last + 1);

  std::string file_vcf;
  for (int argn = 1; argn < argc; argn++)
  {
    std::string arg(argv[argn]);

    if (arg == "-h" || arg == "--help") {
      usage(sofware);
      return 0;
    }
    else if (arg == "-p") {
      vcard::vcard::print_pretty = true;
    }
    else if (arg == "-f") {
      vcard::vcard::print_folding = true;
    }
    else if (arg[0] == '-') {
      ERROR("Unkown option '" << arg << "'");
      return 1;
    }
    else {
      if (file_vcf.empty() == false) {
        ERROR("Error on command line.");
        return 1;
      }
      file_vcf = arg;
    }
  }

  if (file_vcf.empty()) {
    usage(sofware);
    return 1;
  }


  vcard::address_book my_book = vcard::address_book::import(file_vcf);
  std::cout << my_book;

  return 0;
}
