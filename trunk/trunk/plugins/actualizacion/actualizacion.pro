TEMPLATE = lib
CONFIG += plugin
QT += sql \
xml \
network \
debug

DESTDIR = ../../bin/plugins
INCLUDEPATH += ../../src
TARGET = actualizar

HEADERS = formactualizacion.h

SOURCES = actualizacion.cpp \
 formactualizacion.cpp

FORMS = FormActualizacionBase.ui

RESOURCES += actualizacion.qrc

win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
    INCLUDEPATH += ../../src
}
HEADERS -= eactualizacion.h

