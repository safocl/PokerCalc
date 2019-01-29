TARGET = PokerCalc

TEMPLATE = app

INCLUDEPATH += ./include

LIBS += -L./src -lpoker

QMAKE_LFLAGS += -pthread

#CONFIG -= release
#CONFIG -= debug_and_release
#CONFIG -= build_all
#CONFIG *= debug
CONFIG *= console
CONFIG *= c++17
CONFIG *= qt

QT *= core
QT -= gui

#QMAKE_CXXFLAGS_DEBUG *= -O0
#QMAKE_CXXFLAGS_DEBUG *= -std=c++17
#QMAKE_CXXFLAGS_DEBUG *= -g
#QMAKE_CXXFLAGS_DEBUG *= -Wall
#QMAKE_CXXFLAGS_DEBUG *= -Wextra
#QMAKE_CXXFLAGS_DEBUG *= -Wfatal-errors
#QMAKE_CXXFLAGS_DEBUG *= -Werror
#QMAKE_CXXFLAGS_DEBUG *= -pipe
#QMAKE_CXXFLAGS_DEBUG *= -pthread



SOURCES *= main.cpp \
    src/Board.cpp \
    src/Card.cpp \
    src/Deck.cpp \
    src/equity.cpp \
    src/Hand.cpp \
    src/handstrength.cpp \
    main.cpp \
    src/Board.cpp \
    src/Card.cpp \
    src/Deck.cpp \
    src/equity.cpp \
    src/Hand.cpp \
    src/handstrength.cpp \
    main.cpp \
    src/Board.cpp \
    src/Card.cpp \
    src/Deck.cpp \
    src/equity.cpp \
    src/Hand.cpp \
    src/handstrength.cpp \
    main.cpp

HEADERS *= Board.h \
    include/Board.h \
    include/Card.h \
    include/Deck.h \
    include/defines.h \
    include/equity.h \
    include/Hand.h \
    include/handstrength.h

#SUBDIRS += \
#    main.pro \
#    PokerCalc.pro