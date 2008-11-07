SUBDIRS += utiles \
 src \
 plugins \
 utiles/estilos
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread  \
 ordered
DESTDIR = .

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
system( $$join( DIR_EXE, , , '/qcollectiongenerator' ) ayuda/docs.qhcp -o $$DESTDIR/bin/docs.qch )

unix {
  system( generar_pri.sh eliminar )
}
win32 {
  system( generar_pri.bat eliminar )
}

