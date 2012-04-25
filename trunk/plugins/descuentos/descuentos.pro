TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

TARGET = descuentos

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
               ../../utiles \
               ../../reporte

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

QT += sql

OTHER_FILES += descuentos.QSQLITE.sql \
               descuentos.QMYSQL.sql \
    descuentos.QMYSQL.sql \
    descuentos.SQLITE.sql

RESOURCES += descuentos.qrc \
    descuentos.qrc

HEADERS += descuentosplugin.h

SOURCES += descuentosplugin.cpp