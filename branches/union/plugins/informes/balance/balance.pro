TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
help
CONFIG -= release

QT += sql

TARGET = balance

DESTDIR = /home/Esteban/Programas/gestotux/bin/plugins/informes

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3 \
  -o0

INCLUDEPATH += ../../../reporte \
  ../../../utiles

LIBS += ../../../bin/libutiles.a \
  ../../../bin/libncreport.a

TARGETDEPS += ../../../bin/libncreport.a \
  ../../../bin/libutiles.a

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

RCC_DIR = rcc

