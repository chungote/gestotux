TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
help
CONFIG -= release

QT += sql

TARGET = compras

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

TRANSLATIONS += compras.ts

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

# Actualiza la documentacion
DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )SOURCES += mcompra.cpp \
mcompraproductos.cpp \
vcompras.cpp \
formagregarcompra.cpp \
compras.cpp \
../proveedor/mproveedor.cpp \
 dventacompra.cpp
HEADERS += formagregarcompra.h \
mcompra.h \
mcompraproductos.h \
vcompras.h \
compras.h \
../proveedor/mproveedor.h \
 dventacompra.h
FORMS += FormAgregarCompraBase.ui

RESOURCES += compras.qrc
