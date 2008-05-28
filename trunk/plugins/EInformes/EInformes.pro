TEMPLATE = lib

CONFIG += dll \
plugin
TARGET = einformes

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

HEADERS += evisorinforme.h \
../../src/eplugin.h

SOURCES += evisorinforme.cpp

RESOURCES += einformes.qrc

DESTDIR = ../../bin/plugins

