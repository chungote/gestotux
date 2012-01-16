#include "vlistapresupuesto.h"

#include <QTableView>
#include <QHeaderView>
#include <mproductostotales.h>

VListaPresupuesto::VListaPresupuesto(QWidget *parent) :
    EVLista(parent)
{
    this->setObjectName( "vista_presupuesto" );
    this->setWindowTitle( "Listado de items" );
    //this->setWindowIcon( QIcon( ":/imagenes/????.png" ) );

    modelo = new MProductosTotales( this );
    modelo->buscarPrecios( false );
    modelo->calcularTotales( true );
    modelo->setearSoloLectura( true );
    vista->setModel( modelo );

    addAction( ActCerrar );

}

void VListaPresupuesto::setearIdPresupuesto( const int id_presupuesto )
{
  // Cargo todos los datos
    MItemPresupuesto *m = new MItemPresupuesto();
    m->setearId( id_presupuesto );
    m->select();
    for( int i=0; i<m->rowCount(); i++ ) {
        modelo->agregarItem(
                    m->data( m->index( i, 2 ), Qt::EditRole ).toDouble(),
                    m->data( m->index( i, 3 ), Qt::EditRole ).toString(),
                    m->data( m->index( i, 4 ), Qt::EditRole ).toDouble()
                    );
    }
    delete m;
}
