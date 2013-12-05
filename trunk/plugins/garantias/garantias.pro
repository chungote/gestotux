TEMPLATE = lib

CONFIG += plugin \
          dll \
          help

TARGET = garantias

QT += xml \
      network

HEADERS += garantiasplugin.h \
           vgarantias.h \
           mgarantias.h \
           dagregargarantia.h \
           ../ordentrabajo/ecbequipamiento.h \
           ../ordentrabajo/mequipamiento.h
SOURCES += garantiasplugin.cpp \
           vgarantias.cpp \
           mgarantias.cpp \
           dagregargarantia.cpp \
           ../ordentrabajo/ecbequipamiento.cpp \
           ../ordentrabajo/mequipamiento.cpp

DESTDIR = ../../bin/plugins

RESOURCES += garantias.qrc

INCLUDEPATH += ../../utiles \
               ../../src \
               ../ordentrabajo

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}

OTHER_FILES += garantias.QMYSQL.sql \
               garantias.QSQLITE.sql

FORMS += dagregargarantia.ui
