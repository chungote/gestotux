TEMPLATE = lib

CONFIG += dll \
plugin \
debug
CONFIG -= release

QT += sql

TARGET = proveedor

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

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

TRANSLATIONS += proveedor.ts

# Actualiza la documentacion
DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )

SOURCES += dproveedor.cpp \
mproveedor.cpp \
vproveedor.cpp \
 proveedor.cpp
HEADERS += dproveedor.h \
mproveedor.h \
vproveedor.h \
 proveedor.h
