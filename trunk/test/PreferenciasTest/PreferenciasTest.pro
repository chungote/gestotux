#-------------------------------------------------
#
# Project created by QtCreator 2012-10-11T10:35:59
#
#-------------------------------------------------

QT       += sql testlib

TARGET = tst_preferenciastest
CONFIG   += console help
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../utiles \
               ../../src

LIBS += ../../bin/libutiles.a

HEADERS += ../../src/FormPrefDb.h

SOURCES += tst_preferenciastest.cpp \
           ../../src/FormPrefDb.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"