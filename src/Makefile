#srcdir = ..
#incdir = $(srcdir)/include

SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o .a .so

#CXX = /bin/g++
#CXXFLAGS += -Wall -Wextra -Wfatal-errors -Werror -std=c++17 -g
#CXXFLAGS += -I$(incdir)
#LDFLAGS +=
#LDPATH +=
#AR = ar
#ARFLAGS = rcs



sources ::= $(notdir $(wildcard *.cpp))
objects ::= $(sources:.cpp=.o)


.PHONY: all clean


all: $(objects) #libpoker.a

Board.o: $(incdir)/Board.h

Card.o: $(incdir)/Card.h

Deck.o: $(incdir)/Deck.h

Hand.o: $(incdir)/Hand.h

handstrength.o: $(incdir)/handstrength.h

#libpoker.a: $(objects)
#	$(AR) $(ARFLAGS) $@ $(objects)


clean:
	rm -rf $(objects) *.a
