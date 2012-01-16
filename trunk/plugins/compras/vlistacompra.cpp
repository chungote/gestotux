#include "vlistacompra.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QHeaderView>

VListaCompra::VListaCompra(QWidget *parent) :
 EVLista(parent)
{
    setObjectName( "vista_compra" );
    setWindowTitle( "Lista de productos de una compra" );
    addAction( ActCerrar );

    vista->setModel( modelo );
    vista->horizontalHeader()->setAlternatingRowColors( true );
    modelo->setearSoloLectura( true );
    modelo->buscarPrecios( false );
    modelo->calcularTotales( true );
}

void VListaCompra::setearIdCompra( const int id_compra )
{
    QSqlQueryModel cola;
    cola.setQuery(
                QString( "SELECT p.nombre AS \"Producto\", "
                                "c.cantidad AS \"Cantidad\", "
                                "c.precio_compra AS \"Precio Unitario\", "
                                "FROM `compras_productos` AS c, producto AS p "
                                "WHERE id_compra = %1 AND c.id_producto = p.id;" ).arg( id_compra )
                           );
    for( int i = 0; i< cola.rowCount(); i++ ) {
        modelo->agregarItem(
                    cola.data( cola.index( i, 1 ), Qt::EditRole ).toInt(),
                    cola.data( cola.index( i, 0 ), Qt::EditRole ).toString(),
                    cola.data( cola.index( i, 2 ), Qt::EditRole ).toDouble()
                    );
    }
}

