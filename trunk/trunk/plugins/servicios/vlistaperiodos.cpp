#include "vlistaperiodos.h"

#include "mperiodoservicio.h"

#include <QTableView>
#include <QSqlTableModel>
#include <QMessageBox>

VListaPeriodos::VListaPeriodos( int id_servicio, QWidget *parent ) :
    EVLista(parent)
{
    setObjectName( "lista-periodos" );
    setWindowTitle( "Periodos facturados");

    modelo = new MPeriodoServicio( this );
    modelo->inicializar();
    modelo->setFilter( QString( "id_servicio = %1").arg( id_servicio ) );
    modelo->sort( modelo->fieldIndex( "fecha_inicio" ), Qt::AscendingOrder );

    vista->setModel( modelo );
    vista->hideColumn( 0 );
    vista->hideColumn( 1 );
    modelo->select();

    connect( vista, SIGNAL( doubleClicked( QModelIndex ) ), this, SLOT( verFacturacion( QModelIndex ) ) );

    QAction *ActVerFacturacion = new QAction( this );
    ActVerFacturacion->setText( "Ver facturacion" );
    connect( ActVerFacturacion, SIGNAL( triggered() ), this, SLOT( verFacturacion() ) );

    addAction( ActVerFacturacion );
    addAction( ActCerrar );
}

void VListaPeriodos::verFacturacion()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "Por favor, seleccione un periodo para ver si facturación" ) );
        return;
    }
    verFacturacion( vista->selectionModel()->selectedRows().first() );
}

void VListaPeriodos::verFacturacion( QModelIndex idx )
{

}
