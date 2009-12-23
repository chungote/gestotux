TEMPLATE = lib
CONFIG += dll \
    plugin \
    help
QT += sql \
    xml
TARGET = planificador
DESTDIR = ../../bin/plugins/
INCLUDEPATH += ../../src \
    ../../utiles
LIBS += ../../bin/libutiles.a
TARGETDEPS += ../../bin/libutiles.a
OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc
RCC_DIR = rcc
HEADERS += planificadorplugin.h \
    vcalendario.h \
    estilocalendario.h \
    eventocalendario.h \
    itemcalendario.h \
    itemsemana.h
SOURCES += planificadorplugin.cpp \
    vcalendario.cpp \
    estilocalendario.cpp \
    eventocalendario.cpp \
    itemcalendario.cpp \
    itemsemana.cpp
RESOURCES += planificador.qrc
OTHER_FILES += planificador.QSQLITE.sql \
    planificador.QMYSQL.sql
FORMS += appointmentdetailsform.ui
