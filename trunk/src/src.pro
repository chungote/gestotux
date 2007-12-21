SOURCES += gestotux.cpp \
           main.cpp \
 preferencias.cpp \
 eenviobackup.cpp \
 ebackup.cpp \
 eventana.cpp \
 reloj.cpp \
 evlista.cpp \
 formacercade.cpp \
 formagregarrecibo.cpp \
 formmodificarrecibo.cpp \
 formpreferencias.cpp \
 formprefhijo.cpp \
 formulariocentral.cpp \
 fprefgeneral.cpp \
 fprefrecibos.cpp \
 mclientes.cpp \
 mrecibo.cpp \
 recibo.cpp \
 vcliente.cpp \
 visorrecibo.cpp \
 vrecibos.cpp \
 drecibo.cpp \
 eactualizacion.cpp
HEADERS += gestotux.h \
 preferencias.h \
 ebackup.h \
 eenviobackup.h \
 eventana.h \
 reloj.h \
 drecibo.h \
 evlista.h \
 formacercade.h \
 formagregarrecibo.h \
 formmodificarrecibo.h \
 formpreferencias.h \
 formprefhijo.h \
 formulariocentral.h \
 fprefgeneral.h \
 fprefrecibos.h \
 mclientes.h \
 mrecibo.h \
 recibo.h \
 vcliente.h \
 visorrecibo.h \
 vrecibos.h \
 eactualizacion.h \
 einfoprogramainterface.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 exceptions \
 debug
RESOURCES -= application.qrc

CONFIG -= release

QT += sql \
svg \
xml \
network
OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

FORMS += FormAcercaDeBase.ui \
formBackup.ui \
FPrefGeneral.ui \
FormAgregarReciboBase.ui \
FPrefRecibos.ui
RESOURCES += gestotux.qrc

TARGET = gestotux

DESTDIR = ../bin

INCLUDEPATH += ../plugins

