TEMPLATE = lib

CONFIG += staticlib \
          help \
          exceptions

QT += sql \
      xml

TARGET = libctacte

DESTDIR = ../../bin/plugins/

HEADERS += cuentacorrienteplugin.h \
           mcuentacorriente.h \
           mitemcuentacorriente.cpp

SOURCES += cuentacorrienteplugin.cpp \
           mcuentacorriente.cpp \
           mitemcuentacorriente.cpp