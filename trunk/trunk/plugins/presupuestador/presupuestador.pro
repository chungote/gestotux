TEMPLATE = lib
CONFIG += plugin 
TARGET = presupuestador

DESTDIR = ../../bin/plugins
INCLUDEPATH += ../../src

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
 CONFIG += console
}
linux-g++ {
 UI_DIR = ui
 MOC_DIR = moc
     OBJECTS_DIR = obj
}