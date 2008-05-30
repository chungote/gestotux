TEMPLATE = lib
CONFIG += plugin
CONFIG += debug
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
 ../../src/eventana.h \
 ../../src/evlista.h
SOURCES += prespuesto.cpp \
 formagregarpresupuesto.cpp \
 mpresupuesto.cpp \
 presupuesto.cpp \
 mtproductospresupuesto.cpp \
 formlistaproductos.cpp \
 ../../src/eventana.cpp \
 ../../src/evlista.cpp
FORMS += FormPresupuestoBase.ui \
 FormListaProductosBase.ui
TARGET = presupuesto
DESTDIR = ../../bin/plugins
INCLUDEPATH += ../../src
RESOURCES += presupuesto.qrc

