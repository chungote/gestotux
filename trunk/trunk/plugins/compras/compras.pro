TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql

TARGET = compras

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
               ../../utiles \
               ../productos

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
           FormActualizarPrecios.cpp

HEADERS += formagregarcompra.h \
           mcompra.h \
           vcompras.h \
           compras.h \
           mcompraproducto.h \
           ../proveedor/mproveedor.h \
           FormActualizarPrecios.h

OTHER_FILES += compras.QMYSQL.sql \
               compras.QSQLITE.sql



