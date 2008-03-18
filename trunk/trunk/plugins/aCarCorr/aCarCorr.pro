TEMPLATE = lib

CONFIG += dll \
plugin \
debug \
exceptions \
 windows
QT += sql \
svg \
xml \
network


win32 {
    CONFIG += console
}
linux-g++ {
    UI_DIR = ui
    MOC_DIR = moc
    OBJECTS_DIR = obj
}

HEADERS += admincarcorr.h \
 mcategoria.h \
 mestablecimiento.h \
 vcategorias.h \
 evlista.h \
 eventana.h \
 vestablecimiento.h \
 formagregar.h \
 mclientes.h

SOURCES += admincarcorr.cpp \
 mcategoria.cpp \
 mestablecimiento.cpp \
 vcategorias.cpp \
 evlista.cpp \
 eventana.cpp \
 vestablecimiento.cpp \
 formagregar.cpp \
 mclientes.cpp

TARGET = admincaravanascorrientes

DESTDIR = ../../bin/plugins


INCLUDEPATH += ../../src

RESOURCES += aCarCorr.qrc

FORMS += FormAgregarBase.ui

