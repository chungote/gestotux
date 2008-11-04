SOURCES += gestotux.cpp \
           main.cpp \
 eenviobackup.cpp \
 ebackup.cpp \
 reloj.cpp \
 formacercade.cpp \
 formpreferencias.cpp \
 formulariocentral.cpp \
 fprefgeneral.cpp \
 mclientes.cpp \
 vcliente.cpp \
 formactualizacion.cpp \
 esplash.cpp \
 emysql.cpp \
 formprefdb.cpp \
 everificabackup.cpp \
 barralateral.cpp \
 botoneslaterales.cpp
HEADERS += gestotux.h \
 ebackup.h \
 eenviobackup.h \
 reloj.h \
 formacercade.h \
 formpreferencias.h \
 formulariocentral.h \
 fprefgeneral.h \
 mclientes.h \
 vcliente.h \
 einfoprogramainterface.h \
 eplugin.h \
 formactualizacion.h \
 esplash.h \
 emysql.h \
 formprefdb.h \
 everificabackup.h \
 version.h \
 barralateral.h \
 botoneslaterales.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 exceptions \
 debug \
 precompile_header \
 help
QT += sql \
svg \
xml \
network

FORMS += FormAcercaDeBase.ui \
formBackup.ui \
FPrefGeneral.ui \
 FormActualizacionBase.ui \
 EMysql.ui \
 ForPrefDb.ui

TARGET = $$NOMBRE_PROGRAMA
isEmpty( TARGET ) {
  TARGET = gestotux
}



DESTDIR = ../bin

DISTFILES += qt_es.qm \
 ../ayuda/salir.html \
 tablas.QMYSQL.sql \
 tablas.QSQLITE.sql

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

CONFIG -= release

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

LIBS += ../bin/libutiles.a

TARGETDEPS += ../bin/libutiles.a


RESOURCES += gestotux.qrc

TRANSLATIONS += gestotux.ts

INCLUDEPATH += ../utiles \
  ../utiles/ui

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )

QT += webkit