TEMPLATE = lib

CONFIG += dll \
plugin \
debug

QT += sql \
xml

win32 {
    CONFIG += release
    CONFIG -= debug
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
 einforme.h \
 ../../mcategoria.h \
 ../../mestablecimiento.h

SOURCES += informesmovimientos.cpp \
 formfiltro.cpp \
 erenderizadorinforme.cpp \
 einforme.cpp \
 ../../mcategoria.cpp \
 ../../mestablecimiento.cpp


FORMS += FormFiltrosBase.ui

QMAKE_CXXFLAGS_DEBUG += -ggdb \
-g3 \
-O0

DISTFILES += estiloinforme.css

RESOURCES += informe.qrc

CONFIG -= release




LIBS += ../../../../bin/libutiles.a

TARGETDEPS += ../../../../bin/libutiles.a

