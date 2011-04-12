TEMPLATE = lib

CONFIG += dll \
plugin \
help

QT += sql

TARGET = pagos

DESTDIR = ../../bin/plugins/

PRE_TARGETDEPS += ../../bin/libreporte.a \
                  ../../bin/libutiles.a

HEADERS += pagosplugin.h \
           mpagos.h \
           formagregarrecibo.h \
           ../CtaCte/mcuentacorriente.h \
           ../CtaCte/mitemcuentacorriente.h \
           ../caja/mmovimientoscaja.h \
           ../caja/mcajas.h \
           vpagos.h \
           recibo.h \
           FormPrefRecibos.h

SOURCES += pagosplugin.cpp \
           mpagos.cpp \
           formagregarrecibo.cpp \
           ../CtaCte/mcuentacorriente.cpp \
           ../CtaCte/mitemcuentacorriente.cpp \
           ../caja/mmovimientoscaja.cpp \
           ../caja/mcajas.cpp \
           vpagos.cpp \
           recibo.cpp \
           FormPrefRecibos.cpp

FORMS += FormReciboBase.ui \
         FormPrefRecibos.ui

INCLUDEPATH += ../../src \
               ../../reporte \
               ../../utiles \
               ../caja \
               ../CtaCte

LIBS += ../../bin/libreporte.a \
        ../../bin/libutiles.a

TRANSLATIONS += pagos.ts

RESOURCES = pagos.qrc

OTHER_FILES += pagos.QMYSQL.sql \
               pagos.QSQLITE.sql
