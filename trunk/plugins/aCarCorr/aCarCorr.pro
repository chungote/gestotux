
SUBDIRS += aCarCorrPlug.pro

TEMPLATE = lib

CONFIG += dll \
plugin \
exceptions \
 windows \
 debug

QT += sql

HEADERS += admincarcorr.h \
 mcategoria.h \
 mestablecimiento.h \
 vcategorias.h \
 vestablecimiento.h \
 formagregar.h \
 formmudanza.h \
 formmovimiento.h \
 formventa.h \
 mtri.h \
 mcaravanas.h \
 emovimiento.h \
 formstock.h \
 einformeinterface.h \
 TipoMovs.h \
 mcaravanadueno.h \
 formmodificartri.h \
 formprefcaravanas.h \
 mprefcategorias.h \
 evlista.h

SOURCES += admincarcorr.cpp \
 mcategoria.cpp \
 mestablecimiento.cpp \
 vcategorias.cpp \
 vestablecimiento.cpp \
 formagregar.cpp \
 formmudanza.cpp \
 formmovimiento.cpp \
 formventa.cpp \
 mtri.cpp \
 mcaravanas.cpp \
 emovimiento.cpp \
 formstock.cpp \
 mcaravanadueno.cpp \
 formmodificartri.cpp \
 formprefcaravanas.cpp \
 mprefcategorias.cpp \
 evlista.cpp

TARGET = admincaravanascorrientes

DESTDIR = ../../bin/plugins

RESOURCES += aCarCorr.qrc

FORMS += FormMovimientoBase.ui \
 FormPrefCaravanas.ui

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
    QMAKE_EXTRA_TARGETS += /home/ftp/actualizaciones/$TARGET
}
CONFIG -= release

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

INCLUDEPATH += ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

