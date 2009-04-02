TEMPLATE = lib

CONFIG += dll \
plugin \
help

QT += sql \
 svg

TARGET = productos

DESTDIR = ../../bin/plugins

win32 {
    MOC_DIR = win/moc
    UI_DIR = win/ui
    OBJECTS_DIR = win/objeto
}

linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

SOURCES += mcategorias.cpp \
mproductos.cpp \
vcategorias.cpp \
vproductos.cpp \
 productos.cpp \
 dproductos.cpp \
 dcategoria.cpp
HEADERS += mcategorias.h \
mproductos.h \
vcategorias.h \
vproductos.h \
 productos.h \
 dproductos.h \
 dcategoria.h

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
  ../../utiles

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

DISTFILES += productos.SQLITE.sql \
 productos.QMYSQL.sql

TRANSLATIONS += productos.ts
