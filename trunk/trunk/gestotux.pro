SUBDIRS += utiles \
 reporte/libncreport.pro \
 src/src.pro \
 plugins/plugins.pro \
 utiles/estilos/estilos.pro \
 utiles/diseñador/diseñador.pro
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread
DESTDIR = .

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
system( $$join( DIR_EXE, , , '/qcollectiongenerator' ) ayuda/docs.qhcp -o $$DESTDIR/bin/docs.qch )

unix {
    system( generar_pri.sh eliminar )
}
win32 {
    system( generar_pri.bat eliminar )
}
