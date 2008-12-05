TEMPLATE = lib

CONFIG += dll \
plugin \
debug
CONFIG -= release

TARGET = autodestruct

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src


HEADERS += autodestruc.h

SOURCES += autodestruc.cpp

QT += sql

