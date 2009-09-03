TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
help
CONFIG -= release

QT += sql

TARGET = pagos

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a \
  ../../bin/libncreport.a

TARGETDEPS += ../../bin/libncreport.a \
  ../../bin/libutiles.a

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

RCC_DIR = rcc

HEADERS += pagosplugin.h \
 mpagos.h

SOURCES += pagosplugin.cpp \
 mpagos.cpp

