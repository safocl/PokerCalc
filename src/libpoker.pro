VERSION = 0.0.1
TARGET = poker

INCLUDEPATH = ../include

TEMPLATE = lib

CONFIG *= dll
CONFIG *= debug

SOURCES *= Board.cpp
SOURCES *= Card.cpp
SOURCES *= Deck.cpp
SOURCES *= equity.cpp
SOURCES *= Hand.cpp
SOURCES *= handstrength.cpp