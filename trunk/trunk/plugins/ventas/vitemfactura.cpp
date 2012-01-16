#include "vitemfactura.h"
#include <QSqlQueryModel>
#include <QTableView>

VItemFactura::VItemFactura(QWidget *parent) :
    EVLista(parent)
{
    setObjectName( "lista_items_factura" );
    setWindowTitle( "Lista de items de Factura" );

    modelo = new MProductosTotales( this );

    vista->setModel( modelo );
    modelo->setearSoloLectura( true );
    modelo->calcularTotales( true );
    modelo->buscarPrecios( false );

}

void VItemFactura::setearIdFactura( const int id_factura )
{
    QSqlQueryModel *m = new QSqlQueryModel();
    m->setQuery( QString(
                     "SELECT cantidad, texto, precio_unitario"
                     "FROM item_factura "
                     "WHERE id_factura = %1"
                     ).arg( id_factura ) );
    for( int i = 0; i < m->rowCount(); i++ ) {
        modelo->agregarItem(
                    m->data( m->index( i, 0 ), Qt::EditRole ).toInt(),
                    m->data( m->index( i, 1 ), Qt::EditRole ).toString(),
                    m->data( m->index( i, 2 ), Qt::EditRole ).toDouble()
                    );
    }
}
