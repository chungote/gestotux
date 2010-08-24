SUBDIRS += utiles \
 reporte/libncreport.pro \
 src/src.pro \
 plugins/default/default.pro \
 plugins/plugins.pro \
 utiles/estilos/estilos.pro

TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread
DESTDIR = .

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
system( $$join( DIR_EXE, , , '/qcollectiongenerator' ) ayuda/docs.qhcp -o $$DESTDIR/bin/docs.qch )

OTHER_FILES = tareas-pendientes.txt