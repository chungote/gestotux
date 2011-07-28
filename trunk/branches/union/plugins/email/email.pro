TEMPLATE = lib

CONFIG += dll \
plugin \
help

QT += sql \
network

TARGET = email

DESTDIR = ../../bin/plugins/

QMAKE_CXXFLAGS_DEBUG += -o0 \
  -g3 \
  -ggdb

LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

SOURCES += emodelomails.cpp \
eservidoremail.cpp \
mail.cpp \
mime.cpp \
smtp.cpp \
formprefemail.cpp \
email.cpp

HEADERS += emodelomails.h \
eservidoremail.h \
mail.h \
mime.h \
smtp.h \
formprefemail.h \
email.h

FORMS += FormPrefEmailBase.ui

INCLUDEPATH += ../../src \
  ../../utiles

DISTFILES += 	email.QMYSQL.sql \
		email.QSQLITE.sql

RESOURCES += email.qrc

TRANSLATIONS += email.ts

