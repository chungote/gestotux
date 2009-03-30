TEMPLATE = lib

HEADERS += eactcerrar.h \
 eactimprimir.h \
 eventana.h \
 evlista.h \
 preferencias.h \
 evisorinformes.h \
 formprefhijo.h \
 eayuda.h \
 eactguardar.h \
 emcliente.h \
 eeditor.h \
 eactemail.h \
 eregistroplugins.h \
 eactpdf.h \
 eemail.h \
 mail.h \
 mime.h
SOURCES += eactcerrar.cpp \
eactimprimir.cpp \
 eventana.cpp \
 evlista.cpp \
 preferencias.cpp \
 evisorinformes.cpp \
 eayuda.cpp \
 eactguardar.cpp \
 emcliente.cpp \
 eeditor.cpp \
 eactemail.cpp \
 eregistroplugins.cpp \
 eactpdf.cpp \
 eemail.cpp \
 mail.cpp \
 mime.cpp

QT += sql

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

CONFIG += debug \
 staticlib \
 help \
 exceptions

RESOURCES += utiles.qrc

CONFIG -= release

DESTDIR = ../bin

FORMS += EAyudaBase.ui

TRANSLATIONS += utiles.ts

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )







INCLUDEPATH += ../src

