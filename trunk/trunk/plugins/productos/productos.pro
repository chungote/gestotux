TEMPLATE = lib

CONFIG += dll \
plugin \
help

QT += sql

TARGET = productos

DESTDIR = ../../bin/plugins

SOURCES += mcategorias.cpp \
           mproductos.cpp \
           vcategorias.cpp \
           vproductos.cpp \
           productos.cpp \
           dproductos.cpp \
           dcategoria.cpp \
           formprefproductos.cpp
HEADERS += mcategorias.h \
           mproductos.h \
           vcategorias.h \
           vproductos.h \
           productos.h \
           dproductos.h \
           dcategoria.h \
           formprefproductos.h

LIBS += ../../bin/libutiles.a

POST_TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
  ../../utiles

DISTFILES += productos.SQLITE.sql \
 productos.QMYSQL.sql

TRANSLATIONS += productos.ts
RESOURCES += productos.qrc

FORMS += FormPrefProductosBase.ui

OTHER_FILES += productos.QMYSQL.sql \
               productos.QSQLITE.sql
