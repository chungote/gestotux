QT = xml sql gui core
TEMPLATE = lib
CONFIG += warn_on \
          qt \
          thread \
 staticlib \
 debug \
 exceptions
TARGET = ncreport
DEPENDPATH += .
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = uic
# Input
HEADERS += globals.h \
           ncpreview.h \
           ncreport.h \
           ncsqlquery.h \
           ncutils.h \
           reportparser.h \
 	   ereporte.h \
           nciconfactorybase.h \
	   nciconfactory.h
SOURCES += ncpreview.cpp \
           ncreport.cpp \
           ncsqlquery.cpp \
           ncutils.cpp \
           reportparser.cpp \
           ereporte.cpp \
           nciconfactorybase.cpp \
           nciconfactory.cpp
TRANSLATIONS += ncreport_es.ts
DEFINES +=_EXPORTING_NCREPORT
RESOURCES = ncreport.qrc
CONFIG -= release

DESTDIR = ../bin/

INSTALLS -= target

QMAKE_CXXFLAGS_DEBUG += -g3 \
  -o0 \
  -ggdb

INCLUDEPATH += ../utiles \
  .

LIBS += ../bin/libutiles.a

TARGETDEPS += ../bin/libutiles.a

