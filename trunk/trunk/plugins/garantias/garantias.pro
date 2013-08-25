TEMPLATE = lib

CONFIG += plugin \
          dll \
          help

TARGET = garantias

QT += xml \
      network

HEADERS += garantiasplugin.h
SOURCES += garantiasplugin.cpp

DESTDIR = ../../bin/plugins

RESOURCES += garantias.qrc

INCLUDEPATH += ../../utiles \
               ../../src

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}

OTHER_FILES += \
    garantias.QMYSQL.sql
