TEMPLATE = lib
HEADERS += floatstyle.h \
           helpers.h
SOURCES += floatstyle.cpp \
           drawcontrol.cpp \
           helpers.cpp \
           sizes.cpp \
           drawcomplexcontrol.cpp
TARGET = floatstyle
CONFIG += plugin \
 debug \
 dll
RESOURCES = images.qrc
DESTDIR = ../../../bin/styles
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}
