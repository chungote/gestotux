TEMPLATE = lib
CONFIG += dll \
          plugin \
          help

SOURCES +=  ventas.cpp \
            vventas.cpp \
            formagregarventa.cpp \
            ../CtaCte/mcuentacorriente.cpp \
            ../CtaCte/mitemcuentacorriente.cpp \
            ../productos/mproductos.cpp \
            formprefventa.cpp \
            MFactura.cpp \
            mitemfactura.cpp

HEADERS += ventas.h \
           vventas.h \
           formagregarventa.h \
           ../CtaCte/mcuentacorriente.h \
           ../CtaCte/mitemcuentacorriente.h \
           ../productos/mproductos.h \
           formprefventa.h \
           MFactura.h \
           mitemfactura.h

TRANSLATIONS = ventas.ts

QT += sql

TARGET = ventas

DESTDIR = ../../bin/plugins/

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a
PRE_TARGETDEPS += ../../bin/libutiles.a \
                   ../../bin/libreporte.a

FORMS += FormAgregarVentaBase.ui \
         FormPrefVentaBase.ui

INCLUDEPATH +=  ../../src \
                ../../utiles \
                ../../reporte \
                ../productos \
                ../CtaCte

RESOURCES += ventas.qrc

OTHER_FILES += ventas.ts \
               ventas.QSQLITE.sql \
               ventas.QMYSQL.sql
