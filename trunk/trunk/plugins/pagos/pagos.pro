TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
help
CONFIG -= release

QT += sql

TARGET = pagos

DESTDIR = ../../bin/plugins/



TARGETDEPS += ../../bin/libncreport.a \
  ../../bin/libutiles.a

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc


HEADERS += pagosplugin.h \
 mpagos.h \
 formagregarrecibo.h \
 ../CtaCte/mcuentacorriente.h \
 ../CtaCte/mitemcuentacorriente.h \
 vpagos.h \
 recibo.h

SOURCES += pagosplugin.cpp \
 mpagos.cpp \
 formagregarrecibo.cpp \
 ../CtaCte/mcuentacorriente.cpp \
 ../CtaCte/mitemcuentacorriente.cpp \
 vpagos.cpp \
 recibo.cpp

FORMS += FormReciboBase.ui

INCLUDEPATH += ../../src \
  ../../reporte \
  ../../utiles

LIBS += ../../bin/libncreport.a \
  ../../bin/libutiles.a

TRANSLATIONS += pagos.ts
