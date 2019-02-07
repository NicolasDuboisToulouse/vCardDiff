# vCardDiff

Simple [vCard address book](https://www.ietf.org/rfc/rfc2426.txt) diff utility based on [Text::vCard](https://metacpan.org/pod/Text::vCard) and [vCard::AddressBook](https://metacpan.org/pod/vCard::AddressBook).

## Particularity

* Input is supposed to be in UTF-8
* Some fields are ignored as they not represent the contact (date, program ID, ...)
* Program extentions are ignored (field starting with X-)
