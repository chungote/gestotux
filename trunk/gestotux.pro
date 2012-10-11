SUBDIRS += utiles \
           reporte/reporte.pro \
           plugins/default/default.pro \
           plugins/plugins.pro \
           utiles/estilos/estilos.pro \
           src/src.pro \
    test

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