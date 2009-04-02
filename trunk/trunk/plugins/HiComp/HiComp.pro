TEMPLATE = lib
CONFIG += plugin \
 dll \
 help

TARGET = hicomp

HEADERS += hicomp.h \
 visorrecibo.h \
 vrecibos.h \
 recibo.h \
 mrecibo.h \
 drecibo.h \
 formagregarrecibo.h \
 formmodificarrecibo.h \
 fprefrecibos.h \
 filtroclientes.h

SOURCES += hicomp.cpp \
 visorrecibo.cpp \
 vrecibos.cpp \
 recibo.cpp \
 mrecibo.cpp \
 drecibo.cpp \
 formagregarrecibo.cpp \
 formmodificarrecibo.cpp \
 fprefrecibos.cpp \
 filtroclientes.cpp

DESTDIR = ../../bin/plugins

RESOURCES += hicomp.qrc

QT = gui \
	core \
	svg \
	sql \
	xml

FORMS += FormAgregarReciboBase.ui \
 FPrefRecibos.ui	 \
 FiltroClientesBase.ui

DISTFILES += recibo.svg \
 hicomp.SQLITE.sql \
 hicomp.rc

win32 {
    MOC_DIR = win/moc
    UI_DIR = win/ui
    OBJECTS_DIR = win/objeto
}

linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

INCLUDEPATH += ../../utiles

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

TRANSLATIONS += hicomp.ts
