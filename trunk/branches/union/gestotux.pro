SUBDIRS += utiles \
 reporte/reporte.pro \
 src/src.pro \
 plugins/credenciales/credenciales.pro \
 utiles/estilos/estilos.pro

TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread
DESTDIR = .
