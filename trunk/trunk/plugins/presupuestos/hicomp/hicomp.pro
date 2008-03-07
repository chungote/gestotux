TEMPLATE = lib

CONFIG += plugin \
dll
TARGET = hicomp

DESTDIR = ../../../bin/plugins/presupuestos

QT += sql \
svg \
xml
INCLUDEPATH += ../../../src \
../../presupuesto

win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

SOURCES += hicomppresupuesto.cpp

HEADERS += hicomppresupuesto.h

