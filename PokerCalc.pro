TEMPLATE = subdirs

#INCLUDEPATH += include

CONFIG *= ordered
#CONFIG -= relese
#CONFIG *= debug
#CONFIG -= debug_and_release
#CONFIG -= build_all

SUBDIRS *= libpoker main

libpoker.file = src/libpoker.pro

main.file = main.pro
main.depends = libpoker