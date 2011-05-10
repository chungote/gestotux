TEMPLATE = lib
CONFIG += plugin \
          dll \
          help

QT += sql

HEADERS += prespuesto.h \
           formagregarpresupuesto.h \
           mpresupuesto.h \
           presupuesto.h \
           vpresupuesto.h \
           MItemPresupuesto.h \
           ../../src/mclientes.cpp
SOURCES += prespuesto.cpp \
           formagregarpresupuesto.cpp \
           mpresupuesto.cpp \
           presupuesto.cpp \
           vpresupuesto.cpp \
           MItemPresupuesto.cpp \
           ../../src/mclientes.cpp

FORMS += FormPresupuestoBase.ui

TARGET = presupuesto

DESTDIR = ../../bin/plugins

RESOURCES += presupuesto.qrc

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
              ../../utiles

OTHER_FILES += presupuesto.QSQLITE.sql \
               presupuesto.QMYSQL.sql

TRANSLATIONS += presupuesto.ts

