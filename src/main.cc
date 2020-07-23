#include "address_book.hh"

int main()
{
  vcard::address_book my_book = vcard::address_book::import("test.vcf");
  my_book.dump();
  return 0;
}
