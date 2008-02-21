TEMPLATE = lib
CONFIG += plugin 
TARGET = presupuestador

DESTDIR = ../../bin/plugins
INCLUDEPATH += ../../src
TARGETDEPS += ../../bin/gestotux

QT = gui \
	core \
	svg \
	sql \
	xml

OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc

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