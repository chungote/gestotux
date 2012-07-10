TEMPLATE = lib

CONFIG += dll \
          plugin \
          help

QT += sql \
      network

TARGET = email

DESTDIR = ../../bin/plugins/

LIBS += ../../bin/libutiles.a

PRE_TARGETDEPS += ../../bin/libutiles.a

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
           email.h \
           mime-types.h

FORMS += FormPrefEmailBase.ui

INCLUDEPATH += ../../src \
               ../../utiles

OTHER_FILES += email.QMYSQL.sql \
             email.QSQLITE.sql

RESOURCES += email.qrc

TRANSLATIONS += email.ts

