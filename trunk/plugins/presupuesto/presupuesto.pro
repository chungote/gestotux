TEMPLATE = lib
CONFIG += plugin \
          dll \
          help

QT += sql

HEADERS += prespuesto.h \
           formagregarpresupuesto.h \
           mpresupuesto.h \
           presupuesto.h \
           mtproductospresupuesto.h \
           vpresupuesto.h
SOURCES += prespuesto.cpp \
           formagregarpresupuesto.cpp \
           mpresupuesto.cpp \
           presupuesto.cpp \
           mtproductospresupuesto.cpp \
           vpresupuesto.cpp

FORMS += FormPresupuestoBase.ui

TARGET = presupuesto

DESTDIR = ../../bin/plugins

RESOURCES += presupuesto.qrc

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
              ../../utiles

DISTFILES += presupuesto.SQLITE.sql \
             presupuesto.QMYSQL.sql

TRANSLATIONS += presupuesto.ts