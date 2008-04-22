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
 erenderizadorinforme.h \
 mcategoria.h \
 mestablecimiento.h \
 TipoMovs.h \
 einforme.h

SOURCES += informesmovimientos.cpp \
 formfiltro.cpp \
 erenderizadorinforme.cpp \
 mcategoria.cpp \
 mestablecimiento.cpp \
 einforme.cpp

CONFIG -= release


FORMS += FormFiltrosBase.ui

QMAKE_CXXFLAGS_DEBUG += -ggdb \
-g3 \
-O0
INCLUDEPATH += ../..

