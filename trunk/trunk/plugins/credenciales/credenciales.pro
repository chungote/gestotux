TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql

TARGET = credenciales

DESTDIR = ../../bin/plugins/

PRE_TARGETDEPS += ../../bin/libreporte.a \
                  ../../bin/libutiles.a

INCLUDEPATH += ../../src \
               ../../reporte \
               ../../utiles \

LIBS += ../../bin/libreporte.a \
        ../../bin/libutiles.a

HEADERS += DCredencial.h \
    credencialesplugin.h \
    MCredenciales.h \
    mequipos.h \
    vequipos.h \
    vcredenciales.h

SOURCES += DCredencial.cpp \
    credencialesplugin.cpp \
    MCredenciales.cpp \
    mequipos.cpp \
    vequipos.cpp \
    vcredenciales.cpp

FORMS += DCredencial.ui

OTHER_FILES += credenciales.QMYSQL.sql \
    credenciales.QSQLITE.sql

RESOURCES += credenciales.qrc
