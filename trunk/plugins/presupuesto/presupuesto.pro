TEMPLATE = lib
CONFIG += plugin \
          dll \
          help

QT += sql

HEADERS += prespuesto.h \
           formagregarpresupuesto.h \
           mpresupuesto.h \
           vpresupuesto.h \
           MItemPresupuesto.h \
           ../../src/mclientes.cpp
SOURCES += prespuesto.cpp \
           formagregarpresupuesto.cpp \
           mpresupuesto.cpp \
           vpresupuesto.cpp \
           MItemPresupuesto.cpp \
           ../../src/mclientes.cpp

FORMS += FormPresupuestoBase.ui

TARGET = presupuesto

DESTDIR = ../../bin/plugins

RESOURCES += presupuesto.qrc

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

PRE_TARGETDEPS += ../../bin/libutiles.a \
                  ../../bin/libreporte.a

INCLUDEPATH += ../../src \
               ../../utiles \
               ../../reporte

OTHER_FILES += presupuesto.QSQLITE.sql \
               presupuesto.QMYSQL.sql

TRANSLATIONS += presupuesto.ts
