SUBDIRS += utiles \
 src \
 plugins
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread  \
 ordered
DESTDIR = .

$DIR = $$DIRNAME(QMAKE_QMAKE)
system( $$join( $DIR, , , '/qhelpgenerator' ) ayuda/documentacion.qhp -o bin/docs.qhc )