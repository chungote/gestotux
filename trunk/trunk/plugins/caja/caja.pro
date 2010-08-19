TEMPLATE = lib

CONFIG += dll \
plugin

TARGET = caja

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src

QT += sql

OTHER_FILES += caja.QSQLITE.sql \
               caja.QMYSQL.sql

RESOURCES += \
    caja.qrc

HEADERS += \
    caja.h \
    mcajas.h

SOURCES += \
    caja.cpp \
    mcajas.cpp
