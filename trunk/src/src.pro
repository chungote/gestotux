SOURCES += gestotux.cpp \
           main.cpp \
 preferencias.cpp \
 eenviobackup.cpp \
 ebackup.cpp \
 eventana.cpp \
 reloj.cpp \
 evlista.cpp \
 formacercade.cpp \
 formpreferencias.cpp \
 formprefhijo.cpp \
 formulariocentral.cpp \
 fprefgeneral.cpp \
 mclientes.cpp \
 vcliente.cpp \
 mproductos.cpp \
 mcategorias.cpp \
 vproductos.cpp \
 vcategorias.cpp
HEADERS += gestotux.h \
 preferencias.h \
 ebackup.h \
 eenviobackup.h \
 eventana.h \
 reloj.h \
 evlista.h \
 formacercade.h \
 formpreferencias.h \
 formprefhijo.h \
 formulariocentral.h \
 fprefgeneral.h \
 mclientes.h \
 vcliente.h \
 einfoprogramainterface.h \
 mproductos.h \
 mcategorias.h \
 vproductos.h \
 vcategorias.h \
 eplugin.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 exceptions \
 debug
QT += sql \
svg \
xml \
network

linux
{
 OBJECTS_DIR = obj
 MOC_DIR = moc
 UI_DIR = ui
}

FORMS += FormAcercaDeBase.ui \
formBackup.ui \
FPrefGeneral.ui
RESOURCES = gestotux.qrc
TARGET = gestotux
DESTDIR = ../bin
INCLUDEPATH += ../plugins

DISTFILES += qt_es.qm

