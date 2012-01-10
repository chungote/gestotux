TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

SOURCES +=  dgastos.cpp \
            mgasto.cpp \
            vgastos.cpp \
            gastos.cpp \
            formagregargasto.cpp \
            ../caja/mmovimientoscaja.cpp \
            ../caja/mcajas.cpp \
            vcategoriasgastos.cpp \
            mcategoriasgastos.cpp

HEADERS +=  dgastos.h \
            mgasto.h \
            vgastos.h \
            gastos.h \
            formagregargasto.h \
            ../caja/mmovimientoscaja.h \
            ../caja/mcajas.h \
            vcategoriasgastos.h \
            mcategoriasgastos.h

QT += sql

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
               ../../utiles \
               ../../reporte

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

PRE_TARGETDEPS += ../../bin/libutiles.a \
                  ../../bin/libreporte.a

FORMS += FormAgregarGastoBase.ui

RESOURCES += gastos.qrc

TRANSLATIONS += gastos.ts

TARGET = gastos

OTHER_FILES += gastos.QSQLITE.sql \
               gastos.QMYSQL.sql
