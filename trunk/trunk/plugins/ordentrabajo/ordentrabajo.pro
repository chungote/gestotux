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

SOURCES += OrdenTrabajoPlugin.cpp \
    formordentrabajo.cpp
HEADERS += OrdenTrabajoPlugin.h \
    formordentrabajo.h

RESOURCES += ordentrabajo.qrc

OTHER_FILES += ordentrabajo.QMYSQL.sql \
               ordentrabajo.QSQLITE.sql

FORMS += formordentrabajobase.ui

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}
