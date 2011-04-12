TEMPLATE = lib
CONFIG += plugin \
          dll \
          help

TARGET = hicomp

HEADERS += hicomp.h \
           DPagarRecibo.h\
           ../pagos/mpagos.h \
           ../CtaCte/mitemcuentacorriente.h \
           ../CtaCte/mcuentacorriente.h \
           ../caja/mcajas.h

SOURCES += hicomp.cpp \
           DPagarRecibo.cpp \
           ../pagos/mpagos.cpp \
           ../CtaCte/mitemcuentacorriente.cpp \
           ../CtaCte/mcuentacorriente.cpp \
           ../caja/mcajas.cpp

DESTDIR = ../../bin/plugins

RESOURCES += hicomp.qrc

INCLUDEPATH += ../../utiles \
               ../pagos \
               ../../src \
               ../CtaCte \
               ../caja

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

TRANSLATIONS += hicomp.ts

OTHER_FILES += hicomp.QSQLITE.sql \
               hicomp.QMYSQL.sql

FORMS = DPagarReciboBase.ui
