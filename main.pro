TARGET = PokerCalc

TEMPLATE = app

INCLUDEPATH += ./include

LIBS += -L./src

QMAKE_LFLAGS += -lpoker

CONFIG *= debug
CONFIG *= console
CONFIG *= c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_

SOURCES *= main.cpp