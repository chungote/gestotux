TEMPLATE = lib

CONFIG += dll \
plugin \
debug

QT += sql

TARGET = oscarsoraiz

DESTDIR = ../../bin/plugins

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

SOURCES += ../aCarCorr/emovimiento.cpp \
../aCarCorr/formagregar.cpp \
../aCarCorr/formmodificartri.cpp \
../aCarCorr/formmovimiento.cpp \
../aCarCorr/formmudanza.cpp \
../aCarCorr/formstock.cpp \
../aCarCorr/formventa.cpp \
../aCarCorr/mcaravanadueno.cpp \
../aCarCorr/mcaravanas.cpp \
../aCarCorr/mcategoria.cpp \
../aCarCorr/mestablecimiento.cpp \
../aCarCorr/mprefcategorias.cpp \
../aCarCorr/mtri.cpp \
../aCarCorr/vcategorias.cpp \
../aCarCorr/vestablecimiento.cpp \
 oscar.cpp \
 ../aCarCorr/evlista.cpp \
 mduenos.cpp \
 vduenos.cpp \
 formprefinformes.cpp
HEADERS += ../aCarCorr/einformeinterface.h \
../aCarCorr/emovimiento.h \
../aCarCorr/formagregar.h \
../aCarCorr/formmodificartri.h \
../aCarCorr/formmovimiento.h \
../aCarCorr/formmudanza.h \
../aCarCorr/formstock.h \
../aCarCorr/formventa.h \
../aCarCorr/mcaravanadueno.h \
../aCarCorr/mcaravanas.h \
../aCarCorr/mcategoria.h \
../aCarCorr/mestablecimiento.h \
../aCarCorr/mprefcategorias.h \
../aCarCorr/mtri.h \
../aCarCorr/TipoMovs.h \
../aCarCorr/vcategorias.h \
../aCarCorr/vestablecimiento.h \
 oscar.h \
 ../../src/einfoprogramainterface.h \
 ../../src/eplugin.h \
 ../aCarCorr/evlista.h \
 mduenos.h \
 vduenos.h \
 formprefinformes.h

FORMS += ../aCarCorr/FormMovimientoBase.ui \
../aCarCorr/FormPrefCaravanas.ui

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

DEFINES += GESTOTUX_CARAVANAS_TIENEN_DUENOS

RESOURCES += ../aCarCorr/aCarCorr.qrc

CONFIG -= release

INCLUDEPATH += ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

