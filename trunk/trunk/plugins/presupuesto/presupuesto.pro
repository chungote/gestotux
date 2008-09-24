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
    CONFIG += release
    CONFIG -= debug
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
 epresupuesto.h \
 mtproductospresupuesto.h \
 formlistaproductos.h \
 vpresupuesto.h
SOURCES += prespuesto.cpp \
 formagregarpresupuesto.cpp \
 mpresupuesto.cpp \
 presupuesto.cpp \
 mtproductospresupuesto.cpp \
 formlistaproductos.cpp \
 vpresupuesto.cpp
FORMS += FormPresupuestoBase.ui \
 FormListaProductosBase.ui
TARGET = presupuesto
DESTDIR = ../../bin/plugins
RESOURCES += presupuesto.qrc
LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
  ../../utiles

CONFIG -= release

DISTFILES += presupuesto.SQLITE.sql

