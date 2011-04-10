TEMPLATE = lib
CONFIG += plugin \
          dll \
          help

TARGET = hicomp

HEADERS += hicomp.h \
    DPagarRecibo.h

SOURCES += hicomp.cpp \
    DPagarRecibo.cpp

DESTDIR = ../../bin/plugins

RESOURCES += hicomp.qrc

DISTFILES += hicomp.SQLITE.sql \
             hicomp.rc

INCLUDEPATH += ../../utiles \
               ../pagos

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

TRANSLATIONS += hicomp.ts

OTHER_FILES += hicomp.QSQLITE.sql \
               hicomp.QMYSQL.sql

FORMS += \
    DPagarReciboBase.ui
