ifeq ($(OS),Windows_NT)
	BIN_EXTENSION=.exe
	LIB_EXTENSION=.dll
else
	BIN_EXTENSION=
	LIB_EXTENSION=.so
endif


TARGET=parser$(BIN_EXTENSION)
OBJS=string_tools.o vcard.o address_book.o parser.o

all:$(TARGET)

parser$(BIN_EXTENSION): $(OBJS)
	g++ -Wall -Werror -o $@ $(OBJS)

%.o: %.cc
	g++ -Wall -Werror -MMD -c $< -o $@


clean:
	rm -f *~ $(TARGET) $(OBJS) *.d

-include *.d

