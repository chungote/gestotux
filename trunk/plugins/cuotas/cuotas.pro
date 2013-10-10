TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      xml

TARGET = cuotas

DESTDIR = ../../bin/plugins/

PRE_TARGETDEPS += ../../bin/libreporte.a \
                  ../../bin/libutiles.a

INCLUDEPATH += ../../src \
               ../../reporte \
               ../../utiles \
               ../caja \
               ../CtaCte \
               ../pagos \
               ../productos \
               ../descuentos

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a


RESOURCES = cuotas.qrc

OTHER_FILES += cuotas.QMYSQL.sql \
               cuotas.QSQLITE.sql \
               ./../bin/reportes/ResumenCuotas.xml

HEADERS += cuotasplugin.h \
           mplancuota.h \
           formsimularcuotas.h \
           msimularcuotas.h \
           formprefcuotas.h \
           vplancuotas.h \
           mitemplancuota.h \
           mvplancuota.h \
           formdetallecuotas.h \
           DPagoCuota.h \
           formgenerarcomprobantescuotas.h \
           mgenerarcuotas.h \
           ../pagos/mpagos.h \
           ../../src/mclientes.h \
           ../CtaCte/mitemcuentacorriente.h \
           ../CtaCte/mcuentacorriente.h \
           ../caja/mcajas.h \
           ../caja/mmovimientoscaja.h \
           ../remitos/MRemito.h \
           ../remitos/mitemremito.h \
           ../productos/mproductos.h \
           ../ventas/MFactura.h \
           ../ventas/mitemfactura.h \
           ../descuentos/mdescuentos.h \
           formadelantocuotas.h \
           madelantosimularcuotas.h

SOURCES += cuotasplugin.cpp \
           mplancuota.cpp \
           formsimularcuotas.cpp \
           msimularcuotas.cpp \
           formprefcuotas.cpp \
           vplancuotas.cpp \
           mitemplancuota.cpp \
           mvplancuota.cpp \
           formdetallecuotas.cpp \
           DPagoCuota.cpp \
           formgenerarcomprobantescuotas.cpp \
           mgenerarcuotas.cpp \
           ../pagos/mpagos.cpp \
           ../../src/mclientes.cpp \
           ../CtaCte/mitemcuentacorriente.cpp \
           ../CtaCte/mcuentacorriente.cpp \
           ../caja/mcajas.cpp \
           ../caja/mmovimientoscaja.cpp \
           ../remitos/MRemito.cpp \
           ../remitos/mitemremito.cpp \
           ../productos/mproductos.cpp \
           ../ventas/MFactura.cpp \
           ../ventas/mitemfactura.cpp \
           ../descuentos/mdescuentos.cpp \
           formadelantocuotas.cpp \
           madelantosimularcuotas.cpp

FORMS += formsimularcuotasbase.ui \
         formprefcuotasbase.ui \
         formcuotasbase.ui \
         DPagoCuotaBase.ui \
         formgenerarcomprobantescuotasbase.ui

win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}
