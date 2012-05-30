TEMPLATE = lib

CONFIG += dll \
          plugin

QT += sql \
      xml

INCLUDEPATH += ../../src \
               ../../utiles \
               ../../reporte

HEADERS += gestotuxdefault.h

SOURCES += gestotuxdefault.cpp

TARGET = zinfo

DESTDIR = ../../bin/plugins/

TRANSLATIONS += default.ts

RESOURCES += default.qrc

OTHER_FILES += \
    default.QMYSQL.sql \
    default.QSQLITE.sql

