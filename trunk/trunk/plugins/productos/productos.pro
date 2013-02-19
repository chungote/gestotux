TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      xml

TARGET = productos

DESTDIR = ../../bin/plugins

SOURCES += mcategorias.cpp \
           mproductos.cpp \
           vcategorias.cpp \
           vproductos.cpp \
           productos.cpp \
           dproductos.cpp \
           dcategoria.cpp \
           formprefproductos.cpp \
           formagregarproducto.cpp \
           formmodificarproducto.cpp
HEADERS += mcategorias.h \
           mproductos.h \
           vcategorias.h \
           vproductos.h \
           productos.h \
           dproductos.h \
           dcategoria.h \
           formprefproductos.h \
           formagregarproducto.h \
           formmodificarproducto.h

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

PRE_TARGETDEPS += ../../bin/libutiles.a \
                  ../../bin/libreporte.a

INCLUDEPATH += ../../src \
               ../../utiles \
               ../../reporte

DISTFILES += productos.SQLITE.sql \
             productos.QMYSQL.sql

TRANSLATIONS += productos.ts
RESOURCES += productos.qrc

FORMS += FormPrefProductosBase.ui \
         formproductobase.ui

OTHER_FILES += productos.QMYSQL.sql \
               productos.QSQLITE.sql

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}
