TEMPLATE = lib
CONFIG += dll \
plugin \
help

SOURCES += mventa.cpp \
ventas.cpp \
 vventas.cpp \
 mlistaprecio.cpp \
 formagregarventa.cpp \
 mventaproducto.cpp \
 ../CtaCte/mcuentacorriente.cpp \
 ../CtaCte/mitemcuentacorriente.cpp \
    ../productos/mproductos.cpp \
    formprefventa.cpp

HEADERS += mventa.h \
ventas.h \
 vventas.h \
 mlistaprecio.h \
 formagregarventa.h \
 mventaproducto.h \
 ../CtaCte/mcuentacorriente.h \
 ../CtaCte/mitemcuentacorriente.h \
    ../productos/mproductos.h \
    formprefventa.h

TRANSLATIONS = ventas.ts

QT += sql

TARGET = ventas

DESTDIR = ../../bin/plugins/

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a
TARGETDEPS += ../../bin/libutiles.a \
              ../../bin/libreporte.a

FORMS += FormAgregarVentaBase.ui \
 FormPrefVentaBase.ui

INCLUDEPATH += ../../src \
  ../../utiles \
  ../../reporte

RESOURCES += ventas.qrc

OTHER_FILES += ventas.ts \
    ventas.QSQLITE.sql \
    ventas.QMYSQL.sql
