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
           EFlecha.cpp \
    mestadofiscal.cpp \
    ../plugins/credenciales/vequipos.cpp \
    ../plugins/credenciales/DCredencial.cpp \
    ../plugins/credenciales/MCredenciales.cpp \
    ../plugins/credenciales/mequipos.cpp \
    ../plugins/credenciales/vcredenciales.cpp \
    ../plugins/credenciales/dbusquedacredencial.cpp \
    ../plugins/credenciales/credencialesplugin.cpp

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
           EFlecha.h \
    mestadofiscal.h \
    ../plugins/credenciales/vequipos.h \
    ../plugins/credenciales/DCredencial.h \
    ../plugins/credenciales/MCredenciales.h \
    ../plugins/credenciales/mequipos.h \
    ../plugins/credenciales/vcredenciales.h \
    ../plugins/credenciales/dbusquedacredencial.h \
    ../plugins/credenciales/credencialesplugin.h

TEMPLATE = app

CONFIG += warn_on \
          thread \
          qt \
          exceptions \
          help
QT += sql \
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
         FormPantallaInicialBase.ui \
    ../plugins/credenciales/dbusquedacredencial.ui \
    ../plugins/credenciales/DCredencial.ui

TARGET = gestotux

DESTDIR = ../bin

DISTFILES += qt_es.qm

RESOURCES += gestotux.qrc \
    ../plugins/credenciales/credenciales.qrc

TRANSLATIONS += gestotux.ts

PRE_TARGETDEPS += ../bin/libreporte.a \
                   ../bin/libutiles.a

DEFINES += GESTOTUX_DESARROLLO

INCLUDEPATH += ../reporte \
               ../utiles \
               ../utiles/email \
               ../plugins/credenciales

LIBS += ../bin/libutiles.a \
        ../bin/libreporte.a

OTHER_FILES += gestotux.ts \
               tablas.QSQLITE.sql \
               tablas.QMYSQL.sql

exists( cliente.pri ) {
    include( cliente.pri )
}
