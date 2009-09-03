TEMPLATE = lib

CONFIG += dll \
plugin \
help
QT += sql \
xml
TARGET = planificador

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

RCC_DIR = rcc

HEADERS += planificadorplugin.h

SOURCES += planificadorplugin.cpp

