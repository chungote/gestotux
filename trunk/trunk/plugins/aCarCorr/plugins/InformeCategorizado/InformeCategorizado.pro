TEMPLATE = lib

CONFIG += dll \
plugin \
exceptions
QT += sql \
xml
TARGET = informecategorizado

DESTDIR = ../../../../bin/plugins/informes

INCLUDEPATH += ../..

win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}HEADERS += informescategorizados.h

SOURCES += informescategorizados.cpp

