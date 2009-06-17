TEMPLATE = lib

CONFIG += dll \
plugin \
help \
 debug_and_release \
 debug

TARGET = gastos

SOURCES += dgastos.cpp \
mgasto.cpp \
vgastos.cpp \
gastos.cpp \
formagregargasto.cpp

HEADERS += dgastos.h \
mgasto.h \
vgastos.h \
gastos.h \
formagregargasto.h

QT += sql

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


DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
  ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

FORMS += FormAgregarGastoBase.ui

RESOURCES += gastos.qrc

TRANSLATIONS += gastos.tsCONFIG -= release

