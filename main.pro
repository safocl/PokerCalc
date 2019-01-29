TARGET = PokerCalc

TEMPLATE = app

INCLUDEPATH += ./include

LIBS += -L./src

QMAKE_LFLAGS += -lpoker -pthread

CONFIG *= debug
CONFIG *= console
#CONFIG *= c++17
#CONFIG -= release
CONFIG -= qt
CONFIG -= debug_and_release
CONFIG -= build_all

QMAKE_CXXFLAGS_DEBUG *= -O0
QMAKE_CXXFLAGS_DEBUG *= -std=c++17
QMAKE_CXXFLAGS_DEBUG *= -g
QMAKE_CXXFLAGS_DEBUG *= -Wall
QMAKE_CXXFLAGS_DEBUG *= -Wextra
QMAKE_CXXFLAGS_DEBUG *= -Wfatal-errors
QMAKE_CXXFLAGS_DEBUG *= -Werror
QMAKE_CXXFLAGS_DEBUG *= -pipe
#QMAKE_CXXFLAGS_DEBUG *= -pthread



SOURCES *= main.cpp