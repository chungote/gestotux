TEMPLATE = app

SOURCES = verificarLinkeo.cpp

LIBS += ../bin/plugins/libcaja.so \
        ../bin/plugins/libcompras.so \
        ../bin/plugins/libctacte.so \
        ../bin/plugins/libgastos.so \
        ../bin/plugins/libpagos.so \
        ../bin/plugins/libpresupuesto.so \
        ../bin/plugins/libproductos.so \
        ../bin/plugins/libproveedor.so \
        ../bin/plugins/libservicios.so \
        ../bin/plugins/libventas.so \
        ../bin/plugins/libzinfo.so \
#        ../bin/plugins/libdigifauno.so \
        ../bin/libreporte.a \
        ../bin/libutiles.a \
#        ../bin/plugins/libbscomputacion.so
        #../bin/plugins/libhicomp.so