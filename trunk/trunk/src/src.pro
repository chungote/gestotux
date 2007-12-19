SOURCES += gestotux.cpp \
           main.cpp
HEADERS += gestotux.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/gestotux
RESOURCES = application.qrc
