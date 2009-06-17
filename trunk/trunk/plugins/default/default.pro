TEMPLATE = lib

CONFIG += dll \
plugin \
 debug_and_release \
 build_all
INCLUDEPATH += ../../src

HEADERS += gestotuxdefault.h

SOURCES += gestotuxdefault.cpp

TARGET = zinfo

DESTDIR = ../../bin/plugins/

TRANSLATIONS += default.ts

