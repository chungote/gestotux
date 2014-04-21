# Compilación para JHAU-PORA
TEMPLATE = subdirs
CONFIG += warn_on \
          qt \
          thread  \
          ordered

SUBDIRS = reporte/reporte.pro \
          utiles/utiles.pro \
          utiles/estilos/estilos.pro \
          plugins/default/default.pro \
          plugins/CtaCte/CtaCteLib.pro \
          plugins/ventas/VentasLib.pro \
          plugins/caja/CajaLib.pro \
          plugins/cuotas/CuotasLib.pro \
          plugins/descuentos/DescuentosLib.pro \
          plugins/proveedor/proveedor.pro \
          plugins/productos/productos.pro \
          plugins/compras/compras.pro \
          plugins/ventas/ventas.pro \
          src/src.pro \
          plugins/jhau-pora/jhau-pora.pro

NOMBRE_PROGRAMA = acarcorr
ARCHIVO_RC = aCarCorr/icono.rc

unix {
  system( generar_pri.sh $$NOMBRE_PROGRAMA $$ARCHIVO_RC )
}
win32 {
  system( generar_pri.bat $$NOMBRE_PROGRAMA $$ARCHIVO_RC )
}