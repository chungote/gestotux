TEMPLATE = lib
CONFIG += plugin
TARGET = default
DESTDIR = ../../../bin/plugins/presupuestos

win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}


HEADERS += presupuestodefault.h
SOURCES += presupuestodefault.cpp
QT += sql \
svg \
xml
INCLUDEPATH += ../../../src \
../../presupuesto
