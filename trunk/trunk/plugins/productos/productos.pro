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
CONFIG -= release


LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
  ../../utiles

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

RESOURCES += embebido.qrc

DISTFILES += productos.SQLITE.sql \
 productos.QMYSQL.sql

TRANSLATIONS += productos.ts

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )