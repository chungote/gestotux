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
           ../ventas/MItemFactura.h \
           ../CtaCte/MCuentaCorriente.h \
           ../CtaCte/MItemCuentaCorriente.h \
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
           ../ventas/MItemFactura.cpp \
           ../CtaCte/MCuentaCorriente.cpp \
           ../CtaCte/MItemCuentaCorriente.cpp \
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
