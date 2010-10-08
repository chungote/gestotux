TEMPLATE = lib

CONFIG += dll \
plugin \
help

QT += sql

TARGET = compras

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

TRANSLATIONS += compras.ts

FORMS += FormAgregarCompraBase.ui

RESOURCES += compras.qrc

SOURCES += mcompra.cpp \
           vcompras.cpp \
           formagregarcompra.cpp \
           compras.cpp \
           mcompraproducto.cpp \
    ../proveedor/mproveedor.cpp

HEADERS += formagregarcompra.h \
           mcompra.h \
           vcompras.h \
           compras.h \
           mcompraproducto.h \
    ../proveedor/mproveedor.h
