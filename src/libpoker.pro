VERSION = 0.0.1
TARGET = poker

INCLUDEPATH += ../include

TEMPLATE = lib

#CONFIG -= debug_and_release
#CONFIG -= build_all
#CONFIG -= release

CONFIG *= dll
#CONFIG *= debug
CONFIG *= console
CONFIG *= c++17
CONFIG -= qt

#QT *= core
#QT -= gui

QMAKE_CXX = /usr/bin/clang

#QMAKE_CXXFLAGS_DEBUG *= -O0
#QMAKE_CXXFLAGS_DEBUG *= -std=c++17
#QMAKE_CXXFLAGS_DEBUG *= -g
QMAKE_CXXFLAGS_DEBUG *= -Wall
QMAKE_CXXFLAGS_DEBUG *= -Wextra
QMAKE_CXXFLAGS_DEBUG *= -Wfatal-errors
QMAKE_CXXFLAGS_DEBUG *= -Werror
QMAKE_CXXFLAGS_DEBUG *= -pipe

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -mtune=generic
QMAKE_CXXFLAGS_RELEASE -= -march=x86-64
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_CXXFLAGS_RELEASE += -march=native
#QMAKE_CXXFLAGS_RELEASE += -mtune=ivybridge

QMAKE_LFLAGS_SHLIB *= -fPIC

SOURCES *= Board.cpp
SOURCES *= Card.cpp
SOURCES *= Deck.cpp
SOURCES *= equity.cpp
SOURCES *= Hand.cpp
SOURCES *= handstrength.cpp

HEADERS *= Board.h
HEADERS *= Card.h
HEADERS *= Deck.h
HEADERS *= equity.h
HEADERS *= Hand.h
HEADERS *= handstrength.h

#SUBDIRS += \
#    libpoker.pro