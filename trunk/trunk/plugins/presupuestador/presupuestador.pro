TEMPLATE = lib
CONFIG += plugin \
 dll \
help
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
 formpresupuestosanteriores.cpp \
 mpresupuestos.cpp \
 formmodificarpresupuesto.cpp \
 mauto.cpp \
 vautos.cpp \
 edpatente.cpp \
 edmarca.cpp \
 edmodelo.cpp \
 edcolor.cpp
HEADERS += visorresumen.h \
 formnuevopresupuesto.h \
 formpresupuestosanteriores.h \
 mpresupuestos.h \
 formmodificarpresupuesto.h \
 presupuestador.h \
 mauto.h \
 vautos.h \
 edpatente.h \
 edmarca.h \
 edmodelo.h \
 edcolor.h

RESOURCES = prespuestador.qrc
FORMS += FormNuevoPresupuestoBase.ui \
 FormPresupuestosAnterioresBase.ui
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
LIBS += ../../bin/libutiles.a

TARGETDEPS += ../../bin/libutiles.a

INCLUDEPATH += ../../src \
  ../../utiles

TRANSLATIONS += presupuestador.ts

