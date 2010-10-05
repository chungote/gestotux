SOURCES += gestotux.cpp \
           main.cpp \
 eenviobackup.cpp \
 ebackup.cpp \
 reloj.cpp \
 formacercade.cpp \
 formpreferencias.cpp \
 formulariocentral.cpp \
 fprefgeneral.cpp \
 mclientes.cpp \
 vcliente.cpp \
 formactualizacion.cpp \
 esplash.cpp \
 emysql.cpp \
 formprefdb.cpp \
 everificabackup.cpp \
 barralateral.cpp \
 botoneslaterales.cpp \
 formcliente.cpp \
    formplugins.cpp \
    FormPantallaInicial.cpp \
    EFlecha.cpp

HEADERS += gestotux.h \
 ebackup.h \
 eenviobackup.h \
 reloj.h \
 formacercade.h \
 formpreferencias.h \
 formulariocentral.h \
 fprefgeneral.h \
 mclientes.h \
 vcliente.h \
 einfoprogramainterface.h \
 eplugin.h \
 formactualizacion.h \
 esplash.h \
 emysql.h \
 formprefdb.h \
 everificabackup.h \
 version.h \
 barralateral.h \
 botoneslaterales.h \
 formcliente.h \
 einterfazemail.h \
    formplugins.h \
    FormPantallaInicial.h \
    EFlecha.h
TEMPLATE = app
CONFIG += warn_on \
          thread \
          qt \
 exceptions \
 help
QT += sql \
svg \
xml \
network

FORMS += FormAcercaDeBase.ui \
formBackup.ui \
FPrefGeneral.ui \
 FormActualizacionBase.ui \
 EMysql.ui \
 ForPrefDb.ui \
 FormClienteBase.ui \
    formplugins.ui \
    ../utiles/EAyudaBase.ui \
    FormPantallaInicialBase.ui

TARGET = gestotux

DESTDIR = ../bin

DISTFILES += qt_es.qm \
 ../ayuda/salir.html

RESOURCES += gestotux.qrc

TRANSLATIONS += gestotux.ts

QT += webkit

TARGETDEPS += ../bin/libncreport.a \
              ../bin/libutiles.a

DEFINES += GESTOTUX_DESARROLLO

INCLUDEPATH += ../reporte \
  ../utiles \
  ../utiles/email

LIBS += ../bin/libutiles.a \
  ../bin/libncreport.a

OTHER_FILES += \
    gestotux.ts \
    tablas.QSQLITE.sql \
    tablas.QMYSQL.sql
