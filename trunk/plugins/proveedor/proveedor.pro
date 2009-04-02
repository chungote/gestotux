TEMPLATE = lib

CONFIG += dll \
plugin \
help

QT += sql

TARGET = proveedor

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

win32 {
    MOC_DIR = win/moc
    UI_DIR = win/ui
    OBJECTS_DIR = win/objeto
}

linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

TRANSLATIONS += proveedor.ts

SOURCES += dproveedor.cpp \
mproveedor.cpp \
vproveedor.cpp \
 proveedor.cpp
HEADERS += dproveedor.h \
mproveedor.h \
vproveedor.h \
 proveedor.h

DISTFILES += ../../templates/qrc

RESOURCES += proveedor.qrc

