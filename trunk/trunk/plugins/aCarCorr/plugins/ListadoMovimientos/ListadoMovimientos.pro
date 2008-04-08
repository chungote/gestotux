TEMPLATE = lib

CONFIG += dll \
plugin \
debug

QT += sql \
xml

win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

TARGET = movimientos

DESTDIR = ../../../../bin/plugins/informes

HEADERS += informesmovimientos.h \
 formfiltro.h \
 einforme.h \
 erenderizadorinforme.h \
 mcategoria.h \
 mestablecimiento.h \
 TipoMovs.h

SOURCES += informesmovimientos.cpp \
 formfiltro.cpp \
 einforme.cpp \
 erenderizadorinforme.cpp \
 mcategoria.cpp \
 mestablecimiento.cpp

CONFIG -= release

INCLUDEPATH += ../..

FORMS += FormFiltrosBase.ui

