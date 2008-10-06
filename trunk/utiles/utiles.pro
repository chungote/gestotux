TEMPLATE = lib

HEADERS += eactcerrar.h \
eactimprimir.h \
 eventana.h \
 evlista.h \
 preferencias.h \
 evisorinformes.h \
 formprefhijo.h \
 eayuda.h \
 eactguardar.h
SOURCES += eactcerrar.cpp \
eactimprimir.cpp \
 eventana.cpp \
 evlista.cpp \
 preferencias.cpp \
 evisorinformes.cpp \
 eayuda.cpp \
 eactguardar.cpp

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

CONFIG -= release

DESTDIR = ../bin

FORMS += EAyudaBase.ui

