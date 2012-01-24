#include "vlistaperiodos.h"

#include "mperiodoservicio.h"

#include <QTableView>
#include <QSqlTableModel>

VListaPeriodos::VListaPeriodos( int id_servicio, QWidget *parent ) :
    EVLista(parent)
{
    setObjectName( "lista-periodos" );
    setWindowTitle( "Periodos facturados");

    modelo = new MPeriodoServicio( this );
    modelo->inicializar();
    modelo->setFilter( QString( "id_servicio = %1").arg( id_servicio ) );

    vista->setModel( modelo );
    vista->hideColumn( 0 );
    vista->hideColumn( 1 );
    modelo->select();

    addAction( ActCerrar );
}
