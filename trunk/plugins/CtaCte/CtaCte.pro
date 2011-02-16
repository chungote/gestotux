TEMPLATE = lib
CONFIG += dll \
          plugin \
          help
QT += sql
TARGET = ctacte
DESTDIR = ../../bin/plugins/
HEADERS += cuentacorrienteplugin.h \
           formprefctacte.h \
           mcuentacorriente.h \
           vcuentacorriente.h \
           formnuevactacte.h \
           mitemcuentacorriente.h \
           formresumenctacte.h \
           ../pagos/recibo.h
SOURCES += cuentacorrienteplugin.cpp \
           formprefctacte.cpp \
           mcuentacorriente.cpp \
           vcuentacorriente.cpp \
           formnuevactacte.cpp \
           mitemcuentacorriente.cpp \
           formresumenctacte.cpp \
           ../pagos/recibo.cpp
RESOURCES += CtaCte.qrc
FORMS += FormPrefCtaCteBase.ui \
    FormCtaCteBase.ui \
    FormResumenCtaCteBase.ui
DISTFILES += ctacte.QMYSQL.sql \
             ctacte.QSQLITE.sql
TARGETDEPS += ../../bin/libreporte.a \
    ../../bin/libutiles.a
INCLUDEPATH += ../pagos \
               ../../src \
               ../../reporte \
               ../../utiles
LIBS += ../../bin/libutiles.a \
        ../../bin/libreporte.a
TRANSLATIONS += CtaCte.ts
OTHER_FILES +=  CtaCte.ts \
                ctacte.QMYSQL.sql \
                ctacte.QSQLITE.sql
