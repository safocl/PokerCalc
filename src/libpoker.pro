VERSION = 0.0.1
TARGET = poker

INCLUDEPATH += ../include

TEMPLATE = lib

#CONFIG -= debug_and_release
#CONFIG -= build_all
#CONFIG -= release
CONFIG -= app_bundle
CONFIG *= dll
#CONFIG *= debug
#CONFIG *= console
CONFIG *= c++17
CONFIG *= qt
CONFIG *= thread

QT *= core
QT -= gui

QMAKE_CXXFLAGS_RELEASE*= -O3

#QMAKE_CXXFLAGS_DEBUG *= -O0
#QMAKE_CXXFLAGS_DEBUG *= -std=c++17
#QMAKE_CXXFLAGS_DEBUG *= -g
QMAKE_CXXFLAGS_DEBUG *= -Wall
QMAKE_CXXFLAGS_DEBUG *= -Wextra
QMAKE_CXXFLAGS_DEBUG *= -Wfatal-errors
QMAKE_CXXFLAGS_DEBUG *= -Werror
#QMAKE_CXXFLAGS_DEBUG *= -pipe

QMAKE_LFLAGS_SHLIB *= -fPIC

SOURCES *= \
    Board.cpp \
    Card.cpp \
    Deck.cpp \
    equity.cpp \
    Hand.cpp \
    handstrength.cpp \

#HEADERS *= Board.h
#HEADERS *= Card.h
#HEADERS *= Deck.h
#HEADERS *= equity.h
#HEADERS *= Hand.h
#HEADERS *= handstrength.h
#HEADERS *= defines.h

HEADERS += \
    ../include/Board.h \
    ../include/Card.h \
    ../include/Deck.h \
    ../include/defines.h \
    ../include/equity.h \
    ../include/Hand.h \
    ../include/handstrength.h
