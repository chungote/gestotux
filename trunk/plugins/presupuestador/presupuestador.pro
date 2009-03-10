TEMPLATE = lib
CONFIG += plugin \
 dll \
help \
 debug
TARGET = presupuestador

DESTDIR = ../../bin/plugins

QT = gui \
	core \
	svg \
	sql \
	xml

SOURCES += presupuestador.cpp \
 visorresumen.cpp \
 formnuevopresupuesto.cpp \
 mpresupuestos.cpp \
 formmodificarpresupuesto.cpp \
 mauto.cpp \
 vautos.cpp \
 edpatente.cpp \
 edmarca.cpp \
 edmodelo.cpp \
 edcolor.cpp \
 emautos.cpp \
 vpresupuestos.cpp
HEADERS += visorresumen.h \
 formnuevopresupuesto.h \
 mpresupuestos.h \
 formmodificarpresupuesto.h \
 presupuestador.h \
 mauto.h \
 vautos.h \
 edpatente.h \
 edmarca.h \
 edmodelo.h \
 edcolor.h \
 emautos.h \
 vpresupuestos.h

RESOURCES = prespuestador.qrc
FORMS += FormNuevoPresupuestoBase.ui
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



TRANSLATIONS += presupuestador.ts





QMAKE_CXXFLAGS_DEBUG += -ggdb \
  -o0 \
  -g3





CONFIG -= release

INCLUDEPATH += ../../src \
  ../../reporte \
  ../../utiles

LIBS += ../../bin/libncreport.a \
  ../../bin/libemail.a \
  ../../bin/libutiles.a

TARGETDEPS += ../../bin/libemail.a \
  ../../bin/libncreport.a \
  ../../bin/libutiles.a

