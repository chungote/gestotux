TEMPLATE = lib
CONFIG += plugin \
          dll \
          help

QT += sql \
      xml

HEADERS += presupuesto.h \
           formagregarpresupuesto.h \
           mpresupuesto.h \
           vpresupuesto.h \
           MItemPresupuesto.h \
           ../../src/mclientes.cpp \
           mvpresupuestos.h \
           vlistapresupuesto.h \
           formmodificarpresupuesto.h \
           ../descuentos/mdescuentos.h \
           ../ventas/formagregarventa.h \
           ../ventas/MFactura.h \
           ../ventas/mitemfactura.h \
           ../CtaCte/mcuentacorriente.h \
           ../CtaCte/mitemcuentacorriente.h \
           ../caja/mcajas.h \
           ../caja/mmovimientoscaja.h

SOURCES += presupuesto.cpp \
           formagregarpresupuesto.cpp \
           mpresupuesto.cpp \
           vpresupuesto.cpp \
           MItemPresupuesto.cpp \
           ../../src/mclientes.cpp \
           mvpresupuestos.cpp \
           vlistapresupuesto.cpp \
           formmodificarpresupuesto.cpp \
           ../descuentos/mdescuentos.cpp \
           ../ventas/formagregarventa.cpp \
           ../ventas/MFactura.cpp \
           ../ventas/mitemfactura.cpp \
           ../CtaCte/mcuentacorriente.cpp \
           ../CtaCte/mitemcuentacorriente.cpp \
           ../caja/mcajas.cpp \
           ../caja/mmovimientoscaja.cpp

FORMS += FormPresupuestoBase.ui \
         ../ventas/FormAgregarVentaBase.ui

TARGET = presupuesto

DESTDIR = ../../bin/plugins

RESOURCES += presupuesto.qrc

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

PRE_TARGETDEPS += ../../bin/libutiles.a \
                  ../../bin/libreporte.a

INCLUDEPATH += ../../src \
               ../../utiles \
               ../../reporte \
               ../descuentos \
               ../ventas \
               ../productos \
               ../CtaCte \
               ../caja

OTHER_FILES += presupuesto.QSQLITE.sql \
               presupuesto.QMYSQL.sql

TRANSLATIONS += presupuesto.ts
win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}
