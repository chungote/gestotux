TEMPLATE = lib
CONFIG += dll \
plugin \
help

SOURCES += mventa.cpp \
ventas.cpp \
 vventas.cpp \
 edsbprecio.cpp \
 mlistaprecio.cpp \
 formagregarventa.cpp

HEADERS += mventa.h \
ventas.h \
 vventas.h \
 edsbprecio.h \
 mlistaprecio.h \
 formagregarventa.h

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

FORMS += FormAgregarVentaBase.ui

INCLUDEPATH += ../../src \
  ../../utiles

RESOURCES += ventas.qrc

