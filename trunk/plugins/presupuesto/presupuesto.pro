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

DISTFILES += presupuesto.SQLITE.sql \
 presupuesto.QMYSQL.sql

TRANSLATIONS += presupuesto.ts

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )