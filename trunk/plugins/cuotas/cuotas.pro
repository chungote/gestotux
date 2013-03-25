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
               ../CtaCte

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a


RESOURCES = cuotas.qrc

OTHER_FILES += cuotas.QMYSQL.sql \
               cuotas.QSQLITE.sql

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
    mgenerarcuotas.h

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
    mgenerarcuotas.cpp

FORMS += formsimularcuotasbase.ui \
         formprefcuotasbase.ui \
         formcuotasbase.ui \
    DPagoCuotaBase.ui \
    formgenerarcomprobantescuotasbase.ui
win32 {
    QMAKE_LFLAGS += "-Wl,-export-all-symbols"
}
