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
 formactualizacion.cpp \
 esplash.cpp
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
 eplugin.h \
 formactualizacion.h \
 esplash.h
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

FORMS += FormAcercaDeBase.ui \
formBackup.ui \
FPrefGeneral.ui \
 FormActualizacionBase.ui
RESOURCES = gestotux.qrc
TARGET = gestotux
DESTDIR = ../bin
INCLUDEPATH += ../plugins

DISTFILES += qt_es.qm

win32 {
    CONFIG += release
    CONFIG -= debug
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

CONFIG -= release

QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -g3
