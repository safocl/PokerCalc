export srcdir = $(CURDIR)
export incdir = $(srcdir)/include

SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .cpp .o .a .so


#export CXX = /bin/clang++
export CXX = /bin/g++

export CXXFLAGS += -march=sandybridge -mno-aes -fstack-protector-strong
export CXXFLAGS += -Wall -Wextra -Wfatal-errors -Werror -std=c++17 -pipe -O2
CXXFLAGS += -g
CXXFLAGS += -I$(incdir)
CXXFLAGS += -fopenmp

export LDFLAGS += -fopenmp
export LDPATH +=
SRC_DIR = $(srcdir)/src
export AR = ar


EXECUTABLE = PokerCalc

headers ::= $(wildcard $(INC)/*.h)
cpps ::= $(wildcard $(SRC_DIR)/*.cpp)
objects ::= $(cpps:.cpp=.o)


.PHONY: all libobjects clean

all: $(EXECUTABLE)

$(EXECUTABLE): main.o libobjects
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(objects) $< -o $@

main.o: main.cpp $(headers)


libobjects: #$(headers)
	$(MAKE) -C $(SRC_DIR)


clean:
	rm -rf $(EXECUTABLE) *.o
	$(MAKE) -C $(SRC_DIR) clean
