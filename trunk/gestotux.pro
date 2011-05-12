SUBDIRS += utiles \
 reporte/reporte.pro \
 src/src.pro \
 plugins/default/default.pro \
 plugins/plugins.pro \
 utiles/estilos/estilos.pro \
 VerfVal/verlink.pro

TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread
DESTDIR = .

OTHER_FILES = tareas-pendientes.txt

unix {
  system( generar_pri.sh eliminar )
  system( generar_doc_usuario.sh )
}