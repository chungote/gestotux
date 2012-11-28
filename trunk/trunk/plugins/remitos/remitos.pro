TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

SOURCES +=  remitosplugins.cpp \
            ../CtaCte/mcuentacorriente.cpp \
            ../CtaCte/mitemcuentacorriente.cpp \
            ../productos/mproductos.cpp \
           ../caja/mcajas.cpp \
           ../caja/mmovimientoscaja.cpp \
           ../../src/mclientes.cpp \
           ../descuentos/mdescuentos.cpp \
           formprefremito.cpp \
           vremito.cpp \
           vitemremito.cpp \
           MVRemito.cpp \
           formagregarremito.cpp \
           MRemito.cpp \
           mitemremito.cpp

HEADERS += remitosplugins.h \
           ../CtaCte/mcuentacorriente.h \
           ../CtaCte/mitemcuentacorriente.h \
           ../productos/mproductos.h \
           ../caja/mcajas.h \
           ../caja/mmovimientoscaja.h \
           ../../src/mclientes.h \
           ../descuentos/mdescuentos.h \
           formprefremito.h \
           vremito.h \
           vitemremito.h \
           MVRemito.h \
           formagregarremito.h \
           MRemito.h \
           mitemremito.h

QT += sql \
      xml

TARGET = remitos

DESTDIR = ../../bin/plugins/

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

PRE_TARGETDEPS += ../../bin/libutiles.a \
                  ../../bin/libreporte.a

FORMS += FormAgregarRemitoBase.ui \
         FormPrefRemitoBase.ui

INCLUDEPATH +=  ../../src \
                ../../utiles \
                ../../reporte \
                ../productos \
                ../CtaCte \
                ../caja \
                ../descuentos

RESOURCES += remitos.qrc

OTHER_FILES += remitos.QSQLITE.sql \
               remitos.QMYSQL.sql

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}
