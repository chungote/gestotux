#-------------------------------------------------
# Testeo de funcionalidades necesarias para testear
# la cancelacion de un periodo de servicio.
#-------------------------------------------------

QT       += sql testlib
QT       -= gui

INCLUDEPATH += ../.

TARGET = tst_cancelacionperiodoserviciotest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_cancelacionperiodoserviciotest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
