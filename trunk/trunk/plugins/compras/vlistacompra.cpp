#include "vlistacompra.h"
#include <QSqlQueryModel>
#include <QTableView>

VListaCompra::VListaCompra(QWidget *parent) :
 EVLista(parent)
{
    setObjectName( "vista_compra" );
    setWindowTitle( "Lista de productos de una compra" );
    addAction( ActCerrar );
}

void VListaCompra::setearIdCompra( const int id_compra )
{
    QSqlQueryModel *cola = new QSqlQueryModel( this->vista );
    cola->setQuery(
     QString( "SELECT p.nombre AS \"Producto\","
                     "c.precio_compra AS \"Precio Unitario\","
                     "c.cantidad AS \"Cantidad\","
                     "c.cantidad * c.precio_compra AS \"subtotal\""
                     "FROM `compras_productos` AS c, producto AS p"
                     "WHERE id_compra = %1" ).arg( id_compra )
                );
    this->vista->setModel( cola );
}
