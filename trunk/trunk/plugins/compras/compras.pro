TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql

TARGET = compras

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
               ../../utiles \
               ../productos \
               ../caja

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

TRANSLATIONS += compras.ts

FORMS += FormAgregarCompraBase.ui \
         FormActualizarPrecios.ui \
         ../productos/formproductobase.ui

RESOURCES += compras.qrc

SOURCES += mcompra.cpp \
           vcompras.cpp \
           formagregarcompra.cpp \
           compras.cpp \
           mcompraproducto.cpp \
           ../proveedor/mproveedor.cpp \
           ../caja/mmovimientoscaja.cpp \
           ../caja/mcajas.cpp \
           FormActualizarPrecios.cpp \
           vlistacompra.cpp \
           ../productos/formagregarproducto.cpp \
           ../productos/ecbcategoriasproductos.cpp

HEADERS += formagregarcompra.h \
           mcompra.h \
           vcompras.h \
           compras.h \
           mcompraproducto.h \
           ../proveedor/mproveedor.h \
           ../caja/mmovimientoscaja.h \
           ../caja/mcajas.h \
           FormActualizarPrecios.h \
           vlistacompra.h \
           ../productos/formagregarproducto.h \
           ../productos/ecbcategoriasproductos.h

OTHER_FILES += compras.QMYSQL.sql \
               compras.QSQLITE.sql

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}
