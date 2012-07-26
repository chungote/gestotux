TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

CONFIG -= release

QT += sql \
      xml

TARGET = balance

DESTDIR = ../../../bin/plugins/informes

INCLUDEPATH += ../../../reporte \
               ../../../utiles

LIBS += ../../../bin/libutiles.a \
        ../../../bin/libreporte.a

PRE_TARGETDEPS += ../../../bin/libreporte.a \
                  ../../../bin/libutiles.a
