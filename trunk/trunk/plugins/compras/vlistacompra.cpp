#include "vlistacompra.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QHeaderView>

MListaCompra::MListaCompra( QObject *parent )
    : QSqlQueryModel( parent )
{}

void MListaCompra::setearIdCompra( int id_compra )
{
    this->setQuery(
     QString( "SELECT p.nombre AS \"Producto\", "
                     "c.cantidad AS \"Cantidad\", "
                     "c.precio_compra AS \"Precio Unitario\", "
                     "c.cantidad * c.precio_compra AS \"Subtotal\" "
                     "FROM `compras_productos` AS c, producto AS p "
                     "WHERE id_compra = %1 AND c.id_producto = p.id;" ).arg( id_compra )
                );
}

QVariant MListaCompra::data( const QModelIndex &item, int role ) const
{
    if( role == Qt::TextAlignmentRole && item.column() > 0 ) {
        return int( Qt::AlignCenter | Qt::AlignVCenter );
    }
    if( role == Qt::DisplayRole && item.column() > 1 ) {
        return QString( "$ %L1" ).arg( QSqlQueryModel::data( item, role ).toDouble(), 10, 'f', 2 );
    }
    return QSqlQueryModel::data( item, role );
}


VListaCompra::VListaCompra(QWidget *parent) :
 EVLista(parent)
{
    setObjectName( "vista_compra" );
    setWindowTitle( "Lista de productos de una compra" );
    addAction( ActCerrar );
    cola = new MListaCompra( this->vista );
    this->vista->setModel( cola );
}

void VListaCompra::setearIdCompra( const int id_compra )
{
    this->cola->setearIdCompra( id_compra );
    this->vista->horizontalHeader()->setAlternatingRowColors( true );
    this->vista->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
    this->vista->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    this->vista->horizontalHeader()->setMinimumSectionSize( 140 );
}

