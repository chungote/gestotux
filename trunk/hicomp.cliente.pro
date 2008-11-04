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
	plugins/presupuesto/presupuesto/plugins/hicomp.pro \
	plugins/ventas/ventas.pro \
	plugins/gastos/gastos.pro

win32 {
 RC_FILE = plugins/HiComp/icono.rc
}