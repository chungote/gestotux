TEMPLATE = lib

CONFIG += dll \
plugin \
exceptions \
 help \
 debug \
 build_all

QT += sql \
 svg

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
 evlista.h \
 einformeimpresora.h \
 edcategoriaespecial.h

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
 evlista.cpp \
 einformeimpresora.cpp \
 edcategoriaespecial.cpp

TARGET = admincaravanascorrientes

DESTDIR = ../../bin/plugins

RESOURCES += aCarCorr.qrc

FORMS += FormMovimientoBase.ui \
 FormPrefCaravanas.ui

win32 {
    MOC_DIR = win/moc
    UI_DIR = win/ui
    OBJECTS_DIR = win/objeto
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

INCLUDEPATH += ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

DISTFILES += admincaravanascorrientes.SQLITE.sql \
 admincaravanascorrientes.QMYSQL.sql

TRANSLATIONS += admincaravanascorrientes.tsCONFIG -= release

CONFIG -= release
