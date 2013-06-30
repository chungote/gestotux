TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      xml

TARGET = gananciaventa

DESTDIR = ../../../bin/plugins/informes

INCLUDEPATH += ../../../reporte \
               ../../../utiles \
               ../../../src \
               ../. \
               ../../compras \
               ../../ventas

LIBS += ../../../bin/libutiles.a \
        ../../../bin/libreporte.a

PRE_TARGETDEPS += ../../../bin/libreporte.a \
                  ../../../bin/libutiles.a

HEADERS += gananciaventa.h \
    formrangofechas.h

SOURCES += gananciaventa.cpp \
    formrangofechas.cpp

FORMS += \
    FormRangoFechasBase.ui
