TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql

TARGET = servicios

DESTDIR = ../../bin/plugins/

INCLUDEPATH += ../../src \
              ../../reporte \
              ../../utiles

LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a

POST_TARGETDEPS += ../../bin/libreporte.a \
             ../../bin/libutiles.a

OBJECTS_DIR = obj

UI_DIR = ui
MOC_DIR = moc
RCC_DIR = rcc

HEADERS += servicios.h \
           mservicios.h \
           vservicios.h \
           mrecargos.h \
           mcobroservicio.h \
           mrecargoshechos.h \
           formasociarserviciocliente.h \
           formservicio.h \
           edrecargos.h \
           formrecargos.h \
           FormClientesAdheridos.h \
           MClientesServicios.h \
           FormFacturarServicio.h \
           MTempClientesFacturarServicio.h \
           ../pagos/mpagos.h \
           ../CtaCte/mcuentacorriente.h \
           ../CtaCte/mitemcuentacorriente.h
SOURCES += servicios.cpp \
           mservicios.cpp \
           vservicios.cpp \
           mrecargos.cpp \
           mcobroservicio.cpp \
           mrecargoshechos.cpp \
           formasociarserviciocliente.cpp \
           formservicio.cpp \
           edrecargos.cpp \
           formrecargos.cpp \
           FormClientesAdheridos.cpp \
           MClientesServicios.cpp \
           FormFacturarServicio.cpp \
           MTempClientesFacturarServicio.cpp \
           ../pagos/mpagos.cpp \
           ../CtaCte/mcuentacorriente.cpp \
           ../CtaCte/mitemcuentacorriente.cpp

RESOURCES += servicios.qrc

DISTFILES += servicios.QMYSQL.sql \
             servicios.QSQLITE.sql

TRANSLATIONS = servicios.ts

FORMS += FormAsociarBase.ui \
         formServicioBase.ui \
         FormRecargoBase.ui \
         FormClientesAdheridosBase.ui \
         FormFacturarServicioBase.ui

OTHER_FILES += servicios.QMYSQL.sql \
               servicios.QSQLITE.sql