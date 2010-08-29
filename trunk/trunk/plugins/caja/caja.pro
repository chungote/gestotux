TEMPLATE = lib

CONFIG += dll \
plugin \
help

TARGET = caja

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
               ../../utiles

LIBS += ../../bin/libutiles.a \
  ../../bin/libncreport.a

TARGETDEPS += ../../bin/libncreport.a \
  ../../bin/libutiles.a

QT += sql

OTHER_FILES += caja.QSQLITE.sql \
               caja.QMYSQL.sql

RESOURCES += caja.qrc

HEADERS += caja.h \
    mcajas.h \
    vcajas.h \
    FormAgregarCaja.h \
    FormEstadoCaja.h \
    FormCierreCaja.h \
    mmovimientoscaja.h

SOURCES += caja.cpp \
    mcajas.cpp \
    vcajas.cpp \
    FormAgregarCaja.cpp \
    FormEstadoCaja.cpp \
    FormCierreCaja.cpp \
    mmovimientoscaja.cpp

FORMS += FormAgregarCajaBase.ui \
    FormEstadoCajaBase.ui \
    FormCierreCajaBase.ui
