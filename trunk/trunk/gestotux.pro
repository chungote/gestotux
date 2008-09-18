SUBDIRS += utiles \
 src \
 plugins
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread  \
 ordered
DESTDIR = .

DIR_EXE = $$DIRNAME(QMAKE_QMAKE)
system( $$join( DIR_EXE, , , '/qhelpgenerator' ) ayuda/documentacion.qhp -o $$DESTDIR/bin/docs.qch ): DOCS=TRUE