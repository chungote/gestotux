SOURCES += digifauno.cpp \
           mdueno.cpp \
 vduenos.cpp \
 mmascota.cpp \
 formagregarmasctoa.cpp \
 formagregarservicio.cpp \
 mpeluqueria.cpp \
 vmascota.cpp \
 dmascota.cpp \
 eresumen.cpp \
 mrazas.cpp \
 dmiembros.cpp \
 resumengeneral.cpp \
 formprefopciones.cpp \
 formlistapeluqueria.cpp \
 ../proveedor/mproveedor.cpp
HEADERS += digifauno.h \
 mdueno.h \
 mmascota.h \
 formagregarmasctoa.h \
 formagregarservicio.h \
 mpeluqueria.h \
 vmascota.h \
 dmascota.h \
 eresumen.h \
 mrazas.h \
 dmiembros.h \
 resumengeneral.h \
 formprefopciones.h \
 formlistapeluqueria.h \
 vduenos.h \
 ../proveedor/mproveedor.h


CONFIG += warn_on \
	  thread \
          qt \
 exceptions \
 dll \
 plugin


QT += sql

QMAKE_CXXFLAGS_DEBUG += -g \
-o0 \
-ggdb
QMAKE_CXXFLAGS_RELEASE += -o3

RESOURCES = embebido.qrc

FORMS += FormAgregarMascota.ui \
 FormServPeluqueria.ui \
 FPrefGeneral.ui \
 FormPrefOpcionesBase.ui \
 FormListaPeluqueriaBase.ui

linux-g++ {
    OBJECTS_DIR = objeto
    UI_DIR = ui
    MOC_DIR = moc
}


win32 {
    RC_FILE = icono.rc
    MOC_DIR = win/moc
    UI_DIR = win/ui
    OBJECTS_DIR = win/objeto
}
TEMPLATE = lib

DESTDIR = ../../bin/plugins

LIBS += ../../bin/libutiles.a

TRANSLATIONS += digifauno.ts

INCLUDEPATH += ../../src \
  ../../utiles

TARGET = digifauno

TARGETDEPS += ../../bin/libutiles.a
OBJECTS_DIR = objeto/

UI_DIR = ui/

MOC_DIR = moc/

