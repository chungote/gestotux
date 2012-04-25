TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

TARGET = descuentos

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
              ../../utiles

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

QT += sql

OTHER_FILES += descuentos.QSQLITE.sql \
               descuentos.QMYSQL.sql

RESOURCES += descuentos.qrc

HEADERS += descuentosplugin.h \
           formprefdescuentos.h

SOURCES += descuentosplugin.cpp \
           formprefdescuentos.cpp

FORMS += FormPrefDescuentosBase.ui
