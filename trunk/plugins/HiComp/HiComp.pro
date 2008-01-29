TEMPLATE = lib
CONFIG += plugin 
TARGET = hicomp

HEADERS += hicomp.h

SOURCES += hicomp.cpp

DESTDIR = .
INCLUDEPATH += ../../src
TARGETDEPS += ../../bin/gestotux

RESOURCES += hicomp.qrc

