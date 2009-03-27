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
 debug \
 dll \
 plugin


QT += sql

QMAKE_CXXFLAGS_DEBUG += -g \
-o0 \
-ggdb
QMAKE_CXXFLAGS_RELEASE += -o3

RESOURCES = embebido.qrc

DISTFILES += documentacion/digifauno.adp \
	documentacion/gpl-es.txt \
        documentacion/imagenes/ayuda.png \
	documentacion/imagenes/ventanaprincipal.png \
	documentacion/index.html \
	documentacion/partes.html \
	imagenes/add.png \
        imagenes/aplicar.png \
        imagenes/configure.png \
        imagenes/eliminar.png \
        imagenes/fileclose.png \
        imagenes/filefind.png \
        imagenes/filenew.png \
        imagenes/filter.png \
        imagenes/guardar.png \
        imagenes/impresora.png \
        imagenes/imprimir.png \
        imagenes/settings.png \
        imagenes/backup.png \
	imagenes/duenos.png \
	imagenes/resumenes.png \
	imagenes/splash.png \
	imagenes/icono.png \
	imagenes/icono_win.ico \
	imagenes/acroread.png \
	imagenes/pelu.gif \
    	imagenes/compras.jpg \
	imagenes/proveedores.jpg \
	imagenes/mascotas.gif \
	imagenes/productos.jpg \
	imagenes/categorias.jpg \
	imagenes/ventas.jpg \
	imagenes/general.png \
	imagenes/backup2.png \
	imagenes/restaurar.png \
	imagenes/stop.png \
	imagenes/next.png \
	imagenes/diario.png \
	imagenes/mensual.png \
	imagenes/add_user.png \
	imagenes/delete_user.png \
	imagenes/borrar.png \
	imagenes/gasto.jpg \
	imagenes/exit.png \
	imagenes/help.png \
	imagenes/semanal.png \
	imagenes/otras.png \
	icono.rc

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

CONFIG -= release

DESTDIR = ../../bin/plugins

LIBS += ../../bin/libutiles.a


TRANSLATIONS += digifauno.ts

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
message( "Actualizando traduccion" )
message( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
system( $$join( DIR_EXE, , , '/lupdate' ) $$TRANSLATIONS )
INCLUDEPATH += ../../src \
  ../../utiles

TARGET = adigifauno

TARGETDEPS += ../../bin/libutiles.a
OBJECTS_DIR = objeto/

UI_DIR = ui/

MOC_DIR = moc/

