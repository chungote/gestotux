TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
exceptions

QT += sql \
xml

TARGET = informetri

DESTDIR = ../../../../bin/plugins/informes

INCLUDEPATH += ../..

HEADERS += informetri.h

SOURCES += informetri.cpp

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}