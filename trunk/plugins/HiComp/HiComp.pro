TEMPLATE = lib
CONFIG += plugin 
TARGET = hicomp

HEADERS += hicomp.h \
 visorrecibo.h \
 vrecibos.h \
 recibo.h \
 mrecibo.h \
 drecibo.h \
 formagregarrecibo.h \
 formmodificarrecibo.h \
 formprefhijo.h \
 fprefrecibos.h

SOURCES += hicomp.cpp \
 visorrecibo.cpp \
 vrecibos.cpp \
 recibo.cpp \
 mrecibo.cpp \
 drecibo.cpp \
 formagregarrecibo.cpp \
 formmodificarrecibo.cpp \
 formprefhijo.cpp \
 fprefrecibos.cpp

DESTDIR = ../../bin/plugins
INCLUDEPATH += ../../src
TARGETDEPS += ../../bin/gestotux

RESOURCES += hicomp.qrc

QT = gui \
	core \
	svg \
	sql \
	xml

FORMS += FormAgregarReciboBase.ui
OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc	
DISTFILES += recibo.svg

