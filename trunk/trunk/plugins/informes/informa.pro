TEMPLATE = lib

CONFIG += dll \
plugin \
help

TARGET = informes

DESTDIR = ../../bin/plugins/


LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

SOURCES += informesplugin.cpp

HEADERS += informesplugin.h

INCLUDEPATH += ../../src \
  ../../utiles

