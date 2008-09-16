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
 formmodificarpresupuesto.cpp
HEADERS += visorresumen.h \
 formnuevopresupuesto.h \
 formpresupuestosanteriores.h \
 mpresupuestos.h \
 formmodificarpresupuesto.h \
 presupuestador.h

RESOURCES = prespuestador.qrc
FORMS += FormNuevoPresupuestoBase.ui \
 FormPresupuestosAnterioresBase.ui
win32 {
    CONFIG += release
    CONFIG -= debug
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

