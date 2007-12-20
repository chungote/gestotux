SOURCES += gestotux.cpp \
           main.cpp \
 preferencias.cpp \
 eenviobackup.cpp \
 ebackup.cpp \
 eventana.cpp
HEADERS += gestotux.h \
 preferencias.h \
 ebackup.h \
 eenviobackup.h \
 eventana.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 exceptions \
 debug_and_release
TARGET = ../bin/gestotux
RESOURCES -= application.qrc

CONFIG -= release

QT += sql \
svg \
xml \
network
DESTDIR = .

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

FORMS += FormAcercaDeBase.ui \
formBackup.ui \
FPrefGeneral.ui
RESOURCES += gestotux.qrc

