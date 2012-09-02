TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      xml

TARGET = ctacte

DESTDIR = ../../bin/plugins/

HEADERS += cuentacorrienteplugin.h \
           formprefctacte.h \
           mcuentacorriente.h \
           vcuentacorriente.h \
           formnuevactacte.h \
           mitemcuentacorriente.h \
           formresumenctacte.h \
           ../pagos/recibo.h \
           ../pagos/formagregarrecibo.h \
           ../pagos/mpagos.h \
           ../caja/mcajas.h \
           ../caja/mmovimientoscaja.h \
           ../ventas/MFactura.h \
           ../ventas/mitemfactura.h \
           ../descuentos/mdescuentos.h

SOURCES += cuentacorrienteplugin.cpp \
           formprefctacte.cpp \
           mcuentacorriente.cpp \
           vcuentacorriente.cpp \
           formnuevactacte.cpp \
           mitemcuentacorriente.cpp \
           formresumenctacte.cpp \
           ../pagos/recibo.cpp \
           ../pagos/formagregarrecibo.cpp \
           ../pagos/mpagos.cpp \
           ../caja/mcajas.cpp \
           ../caja/mmovimientoscaja.cpp \
           ../ventas/MFactura.cpp \
           ../ventas/mitemfactura.cpp \
           ../descuentos/mdescuentos.cpp

RESOURCES += CtaCte.qrc

FORMS += FormPrefCtaCteBase.ui \
         FormCtaCteBase.ui \
         FormResumenCtaCteBase.ui \
         ../pagos/FormReciboBase.ui

DISTFILES += ctacte.QMYSQL.sql \
             ctacte.QSQLITE.sql

PRE_TARGETDEPS += ../../bin/libreporte.a \
                  ../../bin/libutiles.a

INCLUDEPATH += ../pagos \
               ../caja \
               ../ventas \
               ../productos \
               ../descuentos \
               ../../src \
               ../../reporte \
               ../../utiles

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

TRANSLATIONS += CtaCte.ts

OTHER_FILES +=  CtaCte.ts \
                ctacte.QMYSQL.sql \
                ctacte.QSQLITE.sql
