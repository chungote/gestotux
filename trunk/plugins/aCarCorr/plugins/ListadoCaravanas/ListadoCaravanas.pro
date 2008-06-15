TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
exceptions
CONFIG -= release

QT += sql

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

LIBS += ../../../../bin/libutiles.a

TARGETDEPS += ../../../../bin/libutiles.a

TARGET = listadocaravanas

DESTDIR = /home/Esteban/Programas/gestotux/bin/plugins/informes

HEADERS += listadocaravanas.h

SOURCES += listadocaravanas.cpp

INCLUDEPATH += ../.. \
  ../../../../src \
  ../../../../utiles

