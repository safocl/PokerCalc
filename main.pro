TARGET = PokerCalc

TEMPLATE = app

INCLUDEPATH += ./include

LIBS += -L./src -lpoker

QMAKE_LFLAGS += -pthread

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
QMAKE_CXXFLAGS_DEBUG *= -pthread

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -mtune=generic
QMAKE_CXXFLAGS_RELEASE -= -march=x86-64
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_CXXFLAGS_RELEASE += -march=native
#QMAKE_CXXFLAGS_RELEASE += -mtune=ivybridge

SOURCES *= main.cpp

HEADERS *= include/Board.h \
    include/Card.h \
    include/Deck.h \
    include/defines.h \
    include/equity.h \
    include/Hand.h \
    include/handstrength.h

#SUBDIRS += \
#    main.pro \
#    PokerCalc.pro