TEMPLATE = lib

HEADERS += eactcerrar.h \
eactimprimir.h \
 eventana.h \
 evlista.h \
 preferencias.h \
 evisorinformes.h \
 formprefhijo.h
SOURCES += eactcerrar.cpp \
eactimprimir.cpp \
 eventana.cpp \
 evlista.cpp \
 preferencias.cpp \
 evisorinformes.cpp

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
 staticlib
CONFIG -= release

DESTDIR = ../bin 

