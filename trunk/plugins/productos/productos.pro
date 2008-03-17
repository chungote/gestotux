TEMPLATE = lib

CONFIG += dll \
plugin \
debug

QT += sql

TARGET = productos

DESTDIR = ../../bin/plugins

INCLUDEPATH += ../../src

win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}
SOURCES += mcategorias.cpp \
mproductos.cpp \
vcategorias.cpp \
vproductos.cpp
HEADERS += mcategorias.h \
mproductos.h \
vcategorias.h \
vproductos.h
