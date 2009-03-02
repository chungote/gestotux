TEMPLATE = lib
CONFIG += plugin \
 dll \
 debug \
 help
TARGET = default

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


HEADERS += presupuestodefault.h
SOURCES += presupuestodefault.cpp
QT += sql
INCLUDEPATH += ../.. \
  ../../../../utiles

DESTDIR = ../../../../bin/plugins/presupuestos

CONFIG -= release


LIBS += ../../../../bin/libutiles.a

TARGETDEPS += ../../../../bin/libutiles.a

