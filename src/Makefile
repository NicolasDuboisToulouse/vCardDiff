ifeq ($(OS),Windows_NT)
	BIN_EXTENSION=.exe
	LIB_EXTENSION=.dll
else
	BIN_EXTENSION=
	LIB_EXTENSION=.so
endif


TARGETS = parser$(BIN_EXTENSION) diff-single$(BIN_EXTENSION)

VCARD_OBJS = string_tools.o vcard.o address_book.o diff.o

CFLAGS  = -Wall -Werror -MMD
LDFLAGS = -Wall -Werror -static


all:$(TARGETS)


parser$(BIN_EXTENSION): parser.o libvcard.a
	g++ $(LDFLAGS) -o $@ parser.o libvcard.a

diff-single$(BIN_EXTENSION): diff-single.o libvcard.a
	g++ $(LDFLAGS) -o $@ diff-single.o libvcard.a


libvcard.a: $(VCARD_OBJS)
	rm -f $@
	ar -cru $@ $(VCARD_OBJS)


%.o: %.cc
	g++ $(CFLAGS) -c $< -o $@


clean:
	rm -f *~ $(TARGETS) libvcard.a *.o *.d


-include *.d

