TEMPLATE = lib

CONFIG += plugin \
dll \
debug \
help

TARGET = hicomp


QT += sql

win32 {
    CONFIG += console
    UI_DIR = win/ui
    MOC_DIR = win/moc
    OBJECTS_DIR = win/obj
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

SOURCES += hicomppresupuesto.cpp

HEADERS += hicomppresupuesto.h

INCLUDEPATH += ../.. \
  ../../../../utiles \
  ../../../src \
  ../../presupuesto

DESTDIR = ../../../../bin/plugins/presupuestos

