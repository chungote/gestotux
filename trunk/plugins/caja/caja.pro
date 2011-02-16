TEMPLATE = lib

CONFIG += dll \
plugin \
help

TARGET = caja

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
               ../../utiles

LIBS += ../../bin/libutiles.a \
  ../../bin/libreporte.a

TARGETDEPS += ../../bin/libreporte.a \
  ../../bin/libutiles.a

QT += sql

OTHER_FILES += caja.QSQLITE.sql \
               caja.QMYSQL.sql \
    estilo.css

RESOURCES += caja.qrc

HEADERS += caja.h \
    mcajas.h \
    vcajas.h \
    FormAgregarCaja.h \
    FormEstadoCaja.h \
    FormCierreCaja.h \
    mmovimientoscaja.h \
    formprefcaja.h \
    informecierrecaja.h \
    VResumenCaja.h \
    FormRetiroIngreso.h \
    actingresocaja.h \
    actretirocaja.h \
    acttransferir.h \
    formtransferir.h

SOURCES += caja.cpp \
    mcajas.cpp \
    vcajas.cpp \
    FormAgregarCaja.cpp \
    FormEstadoCaja.cpp \
    FormCierreCaja.cpp \
    mmovimientoscaja.cpp \
    formprefcaja.cpp \
    informecierrecaja.cpp \
    VResumenCaja.cpp \
    FormRetiroIngreso.cpp \
    actingresocaja.cpp \
    actretirocaja.cpp \
    acttransferir.cpp \
    formtransferir.cpp

FORMS += FormAgregarCajaBase.ui \
    FormEstadoCajaBase.ui \
    FormCierreCajaBase.ui \
    formprefcajabase.ui \
    FormRetiroIngresoBase.ui \
    formtransferirbase.ui
