TEMPLATE = lib

CONFIG += dll \
          plugin

INCLUDEPATH += ../../src

HEADERS += gestotuxdefault.h

SOURCES += gestotuxdefault.cpp

TARGET = zinfo

DESTDIR = ../../bin/plugins/

TRANSLATIONS += default.ts

RESOURCES += default.qrc