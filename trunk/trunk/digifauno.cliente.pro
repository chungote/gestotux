# El Fauno  - Veterinaria y peluqueria canina
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread  \
 ordered

NOMBRE_PROGRAMA = digifauno

SUBDIRS = utiles \
        src \
	utiles/estilo/estilo.pro \
	plugins/digifauno/digifauno.pro \
	plugins/ventas/ventas.pro \
	plugins/gastos/gastos.pro \
	plugins/productos/productos.pro

