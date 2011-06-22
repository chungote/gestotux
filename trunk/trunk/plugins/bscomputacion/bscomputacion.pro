HEADERS += bscomputacion.h

SOURCES += bscomputacion.cpp

TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      webkit

TARGET = bscomputacion

DESTDIR = ../../bin/plugins/

PRE_TARGETDEPS += ../../bin/libreporte.a \
                  ../../bin/libutiles.a
#FORMS += FormReciboBase.ui \
#         FormPrefRecibos.ui

INCLUDEPATH += ../../src \
               ../../reporte \
               ../../utiles \
               ../caja \
               ../CtaCte

LIBS += ../../bin/libreporte.a \
        ../../bin/libutiles.a

#TRANSLATIONS += pagos.ts

RESOURCES = bscomputacion.qrc

#OTHER_FILES += pagos.QMYSQL.sql \
#               pagos.QSQLITE.sql
