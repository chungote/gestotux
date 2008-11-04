TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
help

CONFIG -= release

TARGET = gastos


SOURCES += dgastos.cpp \
mgasto.cpp \
vgastos.cpp \
gastos.cpp \
formagregargasto.cpp

HEADERS += dgastos.h \
mgasto.h \
vgastos.h \
gastos.h \
formagregargasto.h

QT += sql

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


DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

TRANSLATIONS += ventas.ts
# Actualiza la documentacion
DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )

FORMS += FormAgregarGastoBase.ui

