TEMPLATE = lib
CONFIG += dll \
plugin \
debug \
help

SOURCES += formagregarventa.cpp \
mventa.cpp \
mventaproducto.cpp \
dventacompra.cpp \
ventas.cpp \
 vventas.cpp \
 edsbprecio.cpp

HEADERS += mventa.h \
formagregarventa.h \
mventaproducto.h \
dventacompra.h \
ventas.h \
 vventas.h \
 edsbprecio.h

TRANSLATIONS = ventas.ts


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
QT += sql

TARGET = ventas

DESTDIR = ../../bin/plugins/

LIBS += ../../bin/libutiles.a
TARGETDEPS += ../../bin/libutiles.a

# Actualiza la documentacion
DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )


FORMS += FormAgregarVentaBase.ui

CONFIG -= release

INCLUDEPATH += ../../src \
  ../../utiles

RESOURCES += ventas.qrc
