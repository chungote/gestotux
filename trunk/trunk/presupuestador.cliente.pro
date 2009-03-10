# Presupuestador - GB
TEMPLATE = subdirs
CONFIG += warn_on \
        qt \
        thread  \
	ordered

SUBDIRS = utiles \
        src \
	reporte/libncreport.pro \
	utiles/estilos \
	plugins/presupuestador
NOMBRE_PROGRAMA = hicomp
ARCHIVO_RC = HiComp/icono.rc

unix {
  system( generar_pri.sh $$NOMBRE_PROGRAMA $$ARCHIVO_RC )
}
win32 {
  system( generar_pri.bat $$NOMBRE_PROGRAMA $$ARCHIVO_RC )
}