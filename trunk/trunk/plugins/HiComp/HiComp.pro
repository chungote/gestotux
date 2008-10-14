TEMPLATE = lib
CONFIG += plugin \
 dll \
 debug
TARGET = hicomp

HEADERS += hicomp.h \
 visorrecibo.h \
 vrecibos.h \
 recibo.h \
 mrecibo.h \
 drecibo.h \
 formagregarrecibo.h \
 formmodificarrecibo.h \
 fprefrecibos.h \
 filtroclientes.h

SOURCES += hicomp.cpp \
 visorrecibo.cpp \
 vrecibos.cpp \
 recibo.cpp \
 mrecibo.cpp \
 drecibo.cpp \
 formagregarrecibo.cpp \
 formmodificarrecibo.cpp \
 fprefrecibos.cpp \
 filtroclientes.cpp

DESTDIR = ../../bin/plugins

RESOURCES += hicomp.qrc

QT = gui \
	core \
	svg \
	sql \
	xml

FORMS += FormAgregarReciboBase.ui \
 FPrefRecibos.ui	 \
 FiltroClientesBase.ui

DISTFILES += recibo.svg \
 ../../CambiosHechos.txt \
 hicomp.SQLITE.sql

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

INCLUDEPATH += ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

CONFIG -= release

CONFIG += help

TRANSLATIONS += hicomp.ts

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
