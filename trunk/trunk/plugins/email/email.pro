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
formprefemail.cpp \
email.cpp \
    smtpclient.cpp \
    quotedprintable.cpp \
    mimetext.cpp \
    mimepart.cpp \
    mimemultipart.cpp \
    mimemessage.cpp \
    mimeinlinefile.cpp \
    mimehtml.cpp \
    mimefile.cpp \
    mimecontentformatter.cpp \
    mimeattachment.cpp \
    emailaddress.cpp \
    enviadoremail.cpp

HEADERS += emodelomails.h \
eservidoremail.h \
formprefemail.h \
email.h \
    SmtpMime \
    smtpclient.h \
    quotedprintable.h \
    mimetext.h \
    mimepart.h \
    mimemultipart.h \
    mimemessage.h \
    mimeinlinefile.h \
    mimehtml.h \
    mimefile.h \
    mimecontentformatter.h \
    mimeattachment.h \
    emailaddress.h \
    enviadoremail.h

FORMS += FormPrefEmailBase.ui

INCLUDEPATH += ../../src \
  ../../utiles

DISTFILES += 	email.QMYSQL.sql \
		email.QSQLITE.sql

RESOURCES += email.qrc

TRANSLATIONS += email.ts

