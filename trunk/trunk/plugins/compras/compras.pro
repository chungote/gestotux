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

SOURCES += mcompra.cpp \
vcompras.cpp \
formagregarcompra.cpp \
compras.cpp \
../proveedor/mproveedor.cpp \
 mcompraproducto.cpp

HEADERS += formagregarcompra.h \
mcompra.h \
vcompras.h \
compras.h \
../proveedor/mproveedor.h \
 mcompraproducto.h
