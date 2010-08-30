TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql

TARGET = servicios

DESTDIR = ../../bin/plugins/

QMAKE_CXXFLAGS_DEBUG += -o0 \
  -g3 \
  -ggdb

INCLUDEPATH += ../../src \
  ../../reporte \
  ../../utiles

LIBS += ../../bin/libutiles.a \
  ../../bin/libncreport.a

TARGETDEPS += ../../bin/libncreport.a \
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
    FormClientesAdheridos.h
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
    FormClientesAdheridos.cpp
RESOURCES += servicios.qrc

DISTFILES += servicios.QMYSQL.sql \
servicios.QSQLITE.sql

TRANSLATIONS = servicios.ts

FORMS += FormAsociarBase.ui \
 formServicioBase.ui \
    FormRecargoBase.ui \
    FormClietnesAdheridosBase.ui

OTHER_FILES += servicios.QMYSQL.sql \
    servicios.QSQLITE.sql
