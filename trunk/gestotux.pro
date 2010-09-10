SUBDIRS += utiles \
 reporte/libncreport.pro \
 src/src.pro \
 plugins/default/default.pro \
 plugins/plugins.pro \
 utiles/estilos/estilos.pro #\
 #reporte/diseñador/diseñador.pro

TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread
DESTDIR = .

OTHER_FILES = tareas-pendientes.txt