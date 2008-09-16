TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
help
QT += sql \
 svg

TARGET = productos

DESTDIR = ../../bin/plugins


win32 {
    CONFIG += release
    CONFIG -= debug
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
 productos.cpp
HEADERS += mcategorias.h \
mproductos.h \
vcategorias.h \
vproductos.h \
 productos.h
CONFIG -= release


LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
  ../../utiles

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

