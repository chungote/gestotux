TEMPLATE = lib
CONFIG += plugin \
		debug
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

RESOURCES += hicomp.qrc

QT = gui \
	core \
	svg \
	sql \
	xml

FORMS += FormAgregarReciboBase.ui \
 FPrefRecibos.ui	
DISTFILES += recibo.svg \
 ../../CambiosHechos.txt

