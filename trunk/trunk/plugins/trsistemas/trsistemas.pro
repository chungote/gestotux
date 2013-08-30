HEADERS += trsistemas.h \
           ../pagos/mpagos.h \
           ../CtaCte/mitemcuentacorriente.h

SOURCES += trsistemas.cpp \
           ../pagos/mpagos.cpp \
           ../CtaCte/mitemcuentacorriente.cpp

TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      webkit \
      xml

TARGET = trsistemas

DESTDIR = ../../bin/plugins/

PRE_TARGETDEPS += ../../bin/libreporte.a \
                  ../../bin/libutiles.a

INCLUDEPATH += ../../src \
               ../../reporte \
               ../../utiles \
               ../caja \
               ../CtaCte \
               ../pagos

LIBS += ../../bin/libreporte.a \
        ../../bin/libutiles.a

RESOURCES = trsistemas.qrc

