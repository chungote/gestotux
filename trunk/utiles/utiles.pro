TEMPLATE = lib

HEADERS += eactcerrar.h \
           eactimprimir.h \
           eventana.h \
           evlista.h \
           preferencias.h \
           evisorinformes.h \
           formprefhijo.h \
           eayuda.h \
           eactguardar.h \
           emcliente.h \
           eeditor.h \
           eactemail.h \
           eregistroplugins.h \
           eactpdf.h \
           eemail.h \
           mail.h \
           mime.h \
           mproductostotales.h \
           dproductostotales.h \
           edsbprecio.h \
           dsino.h \
           EReporte.h \
           ../plugins/productos/mproductos.h \
           NumeroComprobante.h
SOURCES += eactcerrar.cpp \
           eactimprimir.cpp \
           eventana.cpp \
           evlista.cpp \
           preferencias.cpp \
           evisorinformes.cpp \
           eayuda.cpp \
           eactguardar.cpp \
           emcliente.cpp \
           eeditor.cpp \
           eactemail.cpp \
           eregistroplugins.cpp \
           eactpdf.cpp \
           eemail.cpp \
           mail.cpp \
           mime.cpp \
           mproductostotales.cpp \
           dproductostotales.cpp \
           edsbprecio.cpp \
           dsino.cpp \
           ../plugins/productos/mproductos.cpp \
           NumeroComprobante.cpp \
           EReporte.cpp

QT += sql

CONFIG +=   staticlib \
            help \
            exceptions \
            debug

RESOURCES += utiles.qrc

DESTDIR = ../bin

FORMS += EAyudaBase.ui

TRANSLATIONS += utiles.ts

INCLUDEPATH += ../src \
               ../reporte
