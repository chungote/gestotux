TEMPLATE = lib
win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

TARGET = senasa
CONFIG += dll \
plugin \
exceptions \
windows
QT += sql

DESTDIR = ../../../../bin/plugins/informes

HEADERS += senasa.h

SOURCES += senasa.cpp

INCLUDEPATH += ../..

