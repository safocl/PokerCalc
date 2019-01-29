TEMPLATE = subdirs

CONFIG *= ordered
CONFIG *= qt

INCLUDEPATH += ./include

SUBDIRS *= libpoker main

libpoker.file = src/libpoker.pro

main.file = main.pro
main.depends = libpoker