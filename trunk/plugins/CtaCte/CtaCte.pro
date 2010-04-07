TEMPLATE = lib
CONFIG += dll \
    plugin \
    help
CONFIG -= release
QT += sql
TARGET = ctacte
DESTDIR = ../../bin/plugins/
QMAKE_CXXFLAGS_DEBUG += -ggdb \
    -g3 \
    -o0
OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc
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
TARGETDEPS += ../../bin/libncreport.a \
    ../../bin/libutiles.a
INCLUDEPATH += ../pagos \
    ../../src \
    ../../reporte \
    ../../utiles
LIBS += ../../bin/libutiles.a \
    ../../bin/libncreport.a
TRANSLATIONS += CtaCte.ts
