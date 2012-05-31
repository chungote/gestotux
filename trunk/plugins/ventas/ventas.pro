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
           ../caja/mcajas.cpp \
           ../caja/mmovimientoscaja.cpp \
            mitemfactura.cpp \
           ../../src/mclientes.cpp \
           MVFacturas.cpp \
           vitemfactura.cpp \
           ../descuentos/mdescuentos.cpp

HEADERS += ventas.h \
           vventas.h \
           formagregarventa.h \
           ../CtaCte/mcuentacorriente.h \
           ../CtaCte/mitemcuentacorriente.h \
           ../productos/mproductos.h \
           formprefventa.h \
           MFactura.h \
           ../caja/mcajas.h \
           ../caja/mmovimientoscaja.h \
           mitemfactura.h \
           ../../src/mclientes.h \
           MVFacturas.h \
           vitemfactura.h \
           ../descuentos/mdescuentos.h

TRANSLATIONS = ventas.ts

QT += sql \
      xml

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
                ../CtaCte \
                ../caja \
                ../descuentos \
                ../pagos

RESOURCES += ventas.qrc

OTHER_FILES += ventas.ts \
               ventas.QSQLITE.sql \
               ventas.QMYSQL.sql
