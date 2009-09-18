CONFIG += warn_on \
          qt \
          thread \
 debug \
 help \
 exceptions
TEMPLATE = app
HEADERS += ncreportdesignerdesignarea.h \
           ncreportdesignersizehandler.h \
           ncreportdesignerwindow.h \
           ncreportdesignerdocument.h \
           ncreportdesignercommand.h \
           ncreportdesignerwidgetfactory.h \
           ncreportdesignerwidget.h \
           measurement.h \
           ncreportdesignerresourcehandler.h \
           globals.h \
           ncreportdesignerwidgetsetdialog.h \
           nccolorcombo.h \
           ncreportdesignerwidgetsetdialogui.h \
           diaquery.h \
           diagroup.h \
           reportvariablelistview.h \
           diavariable.h \
           diapage.h \
           ncaboutdialog.h
SOURCES += main.cpp \
           ncreportdesignerdesignarea.cpp \
           ncreportdesignersizehandler.cpp \
           ncreportdesignerwindow.cpp \
           ncreportdesignerdocument.cpp \
           ncreportdesignercommand.cpp \
           ncreportdesignerwidgetfactory.cpp \
           ncreportdesignerwidget.cpp \
           measurement.cpp \
           ncreportdesignerresourcehandler.cpp \
           ncreportdesignerwidgetsetdialog.cpp \
           nccolorcombo.cpp \
           ncreportdesignerwidgetsetdialogui.cpp \
           diaquery.cpp \
           diagroup.cpp \
           reportvariablelistview.cpp \
           diavariable.cpp \
           diapage.cpp \
           ncaboutdialog.cpp

QT += sql \
xml \
opengl
TARGET = disenador

DESTDIR = /home/Esteban/Programas/gestotux/bin

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

TRANSLATIONS += diseñador.ts

CONFIG -= release

RESOURCES += diseñador.qrc

