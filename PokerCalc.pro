TEMPLATE = subdirs

#INCLUDEPATH += include

CONFIG *= ordered

SUBDIRS *= libpoker main

libpoker.file = src/libpoker.pro

main.file = main.pro
main.depends = libpoker