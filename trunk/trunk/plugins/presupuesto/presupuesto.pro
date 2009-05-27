TEMPLATE = lib
CONFIG += plugin \
 dll \
 debug \
 help

QT = gui \
	core \
	svg \
	sql \
	xml

win32 {
    MOC_DIR = win/moc
    UI_DIR = win/ui
    OBJECTS_DIR = win/objeto
}

linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

HEADERS += prespuesto.h \
 formagregarpresupuesto.h \
 mpresupuesto.h \
 presupuesto.h \
 mtproductospresupuesto.h \
 vpresupuesto.h
SOURCES += prespuesto.cpp \
 formagregarpresupuesto.cpp \
 mpresupuesto.cpp \
 presupuesto.cpp \
 mtproductospresupuesto.cpp \
 vpresupuesto.cpp
FORMS += FormPresupuestoBase.ui
TARGET = presupuesto
DESTDIR = ../../bin/plugins
RESOURCES += presupuesto.qrc
LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
  ../../utiles \
  .

DISTFILES += presupuesto.SQLITE.sql \
 presupuesto.QMYSQL.sql

TRANSLATIONS += presupuesto.ts