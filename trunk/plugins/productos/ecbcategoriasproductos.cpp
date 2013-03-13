#include "ecbcategoriasproductos.h"

ECBCategoriasProductos::ECBCategoriasProductos( QWidget *parent ) :
    ECBTabla(parent)
{
    this->setearTabla( "categoria_producto" );
    this->setearCampoId( "id" );
    this->setearCampoTexto( "nombre" );
    this->setearCampoOrden( "nombre" );
}
