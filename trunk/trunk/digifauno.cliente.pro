# El Fauno  - Veterinaria y peluqueria canina
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread  \
 ordered

SUBDIRS = utiles \
        src \
	utiles/estilo/estilo.pro \
	plugins/digifauno/digifauno.pro \
	plugins/ventas/ventas.pro \
	plugins/gastos/gastos.pro \
	plugins/productos/productos.pro

NOMBRE_PROGRAMA = Digifauno
ARCHIVO_RC = digifauno/icono.rc

system( generar_pri.sh $$NOMBRE_PROGRAMA $$ARCHIVO_RC )
