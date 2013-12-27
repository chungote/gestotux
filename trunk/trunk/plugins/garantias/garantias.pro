TEMPLATE = lib

CONFIG += plugin \
          dll \
          help \
          excpetions \
          rtti

TARGET = garantias

QT += xml \
      network

HEADERS += garantiasplugin.h \
           vgarantias.h \
           mgarantias.h \
           dagregargarantia.h \
           formprefgarantias.h
SOURCES += garantiasplugin.cpp \
           vgarantias.cpp \
           mgarantias.cpp \
           dagregargarantia.cpp \
           formprefgarantias.cpp

DESTDIR = ../../bin/plugins

RESOURCES += garantias.qrc

INCLUDEPATH += ../../utiles \
               ../../src \
               ../../reporte \
               ../ordentrabajo \
               ../ventas

PRE_TARGETDEPS += ../../bin/libutiles.a

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}

OTHER_FILES += garantias.QMYSQL.sql \
               garantias.QSQLITE.sql

FORMS += dagregargarantia.ui \
    formprefgarantias.ui

QMAKE_LFLAGS += -Wl,-rpath,./plugins

LIBS += -L../../bin \
        -L../../bin/plugins \
        -lutiles \
        -lreporte \
        -lordentrabajo \
        -lventas
