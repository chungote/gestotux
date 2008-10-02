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
system( $$join( DIR_EXE, , , '/qcollectiongenerator' ) ayuda/docs.qhcp -o $$DESTDIR/bin/docs.qch ): DOCS=TRUE