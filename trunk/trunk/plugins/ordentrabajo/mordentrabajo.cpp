#include "mordentrabajo.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


MOrdenTrabajo::MOrdenTrabajo( QObject *parent ) :
QSqlRelationalTableModel( parent )
{
    setTable( "orden_trabajo" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "#Cliente" );
    setHeaderData( 2, Qt::Horizontal, "Fecha de Ingreso" );
    setHeaderData( 3, Qt::Horizontal, "Requerente" );
    setHeaderData( 4, Qt::Horizontal, "Ingresante" );
    setHeaderData( 5, Qt::Horizontal, "Fecha de Vencimiento" );
    setHeaderData( 6, Qt::Horizontal, "Fecha de Devolucion" );
    setHeaderData( 7, Qt::Horizontal, "#Equipamiento" );
    setHeaderData( 8, Qt::Horizontal, "#Factura" );
}

bool MOrdenTrabajo::tieneDatosRelacionados( const int /* id_orden_trabajo */ )
{
    // Las ordenes de trabajo implican la eliminacion de todos los datos relacionados ( operacion_orden_trabajo )
    return false;
}

NumeroComprobante MOrdenTrabajo::numeroComprobanteProximo()
{
    return NumeroComprobante( 0, 0, 0 );
}

NumeroComprobante MOrdenTrabajo::numeroComprobanteSegunId( const int id_orden )
{
}

int MOrdenTrabajo::idSegunNumeroComprobante(NumeroComprobante num)
{
}


