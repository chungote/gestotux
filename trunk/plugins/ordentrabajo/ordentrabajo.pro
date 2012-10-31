TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      xml

TARGET = ordentrabajo

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
               ../../utiles \
               ../../reporte

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

PRE_TARGETDEPS += ../../bin/libutiles.a \
                  ../../bin/libreporte.a

SOURCES += OrdenTrabajoPlugin.cpp
HEADERS += OrdenTrabajoPlugin.h

RESOURCES += ordentrabajo.qrc

OTHER_FILES += ordentrabajo.QMYSQL.sql \
               ordentrabajo.QSQLITE.sql