#include "error.hh"
#include "address_book.hh"

void usage(std::string software)
{
  MSG("USAGE: " << software << " [-p|-f] <file_left.vcf> <file_right.vcf>");
  MSG("  Compare fisrt <file_left.vcf> vcard to first <file_right.vcf> vcard.");
  MSG("  For testing purpose");
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

  std::string left_vcf;
  std::string right_vcf;
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
      if (left_vcf.empty()) {
        left_vcf = arg;
      } else if (right_vcf.empty()) {
        right_vcf = arg;
      } else {
        ERROR("Error on command line.");
        return 1;
      }
    }
  }

  if (left_vcf.empty() || right_vcf.empty()) {
    usage(sofware);
    return 1;
  }


  vcard::address_book left_book = vcard::address_book::import(left_vcf);
  vcard::address_book right_book = vcard::address_book::import(right_vcf);

  left_book.first().show_diff(right_book.first());

  return 0;
}
