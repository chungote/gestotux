# HiComp Computación - Sergio Sack
TEMPLATE = subdirs
CONFIG += warn_on \
        qt \
        thread  \
	ordered

SUBDIRS = utiles/utiles.pro \
        src/src.pro \
	utiles/estilo/estilo.pro \
	plugins/HiComp/HiComp.pro \
	plugins/productos/productos.pro \
	plugins/presupuesto/presupuesto.pro \
	plugins/presupuesto/plugins/default/default.pro \
	plugins/presupuesto/plugins/hicomp/hicomp.pro \
	plugins/ventas/ventas.pro \
	plugins/gastos/gastos.pro \
	plugins/compras/compras.pro \
	plugins/proveedor/proveedor.pro

NOMBRE_PROGRAMA = hicomp
ARCHIVO_RC = HiComp/icono.rc

unix {
  system( generar_pri.sh $$NOMBRE_PROGRAMA $$ARCHIVO_RC )
}
win32 {
  system( generar_pri.bat $$NOMBRE_PROGRAMA $$ARCHIVO_RC )
}