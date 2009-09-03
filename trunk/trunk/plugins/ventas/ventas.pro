TEMPLATE = lib
CONFIG += dll \
plugin \
help \
 debug

SOURCES += mventa.cpp \
ventas.cpp \
 vventas.cpp \
 mlistaprecio.cpp \
 formagregarventa.cpp \
 mventaproducto.cpp \
 vlistaprecio.cpp \
 ../CtaCte/mcuentacorriente.cpp \
 ../CtaCte/mitemcuentacorriente.cpp

HEADERS += mventa.h \
ventas.h \
 vventas.h \
 mlistaprecio.h \
 formagregarventa.h \
 mventaproducto.h \
 vlistaprecio.h \
 ../CtaCte/mcuentacorriente.h \
 ../CtaCte/mitemcuentacorriente.h

TRANSLATIONS = ventas.ts


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
QT += sql

TARGET = ventas

DESTDIR = ../../bin/plugins/

LIBS += ../../bin/libutiles.a
TARGETDEPS += ../../bin/libutiles.a

FORMS += FormAgregarVentaBase.ui \
 FormPrefVentaBase.ui

INCLUDEPATH += ../../src \
  ../../utiles

RESOURCES += ventas.qrc
