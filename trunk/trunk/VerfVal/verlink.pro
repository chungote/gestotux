TEMPLATE = app

SOURCES = verificarLinkeo.cpp

LIBS += ../../gestotux-build-desktop/bin/plugins/libcaja.so \
        ../../gestotux-build-desktop/bin/plugins/libcompras.so \
        ../../gestotux-build-desktop/bin/plugins/libctacte.so \
        ../../gestotux-build-desktop/bin/plugins/libgastos.so \
        ../../gestotux-build-desktop/bin/plugins/libpagos.so \
        ../../gestotux-build-desktop/bin/plugins/libpresupuesto.so \
        ../../gestotux-build-desktop/bin/plugins/libproductos.so \
        ../../gestotux-build-desktop/bin/plugins/libproveedor.so \
        ../../gestotux-build-desktop/bin/plugins/libservicios.so \
        ../../gestotux-build-desktop/bin/plugins/libventas.so \
        ../../gestotux-build-desktop/bin/plugins/libzinfo.so \
        ../../gestotux-build-desktop/bin/plugins/libdigifauno.so \
        ../../gestotux-build-desktop/bin/libreporte.a \
        ../../gestotux-build-desktop/bin/libutiles.a

system( touch verificarLinkeo.cpp )