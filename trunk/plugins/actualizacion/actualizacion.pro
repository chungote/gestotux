TEMPLATE = lib
CONFIG += plugin
QT += sql \
xml \
network

DESTDIR = ../../bin/plugins
INCLUDEPATH += ../../src
TARGET = actualizar

OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc

HEADERS = actualizacion.h

SOURCES = actualizacion.cpp

FORMS = FormActualizacionBase.ui

