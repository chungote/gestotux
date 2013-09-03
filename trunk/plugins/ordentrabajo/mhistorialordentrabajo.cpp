#include "mhistorialordentrabajo.h"

MHistorialOrdenTrabajo::MHistorialOrdenTrabajo(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable( "operacion_orden_trabajo" );
    setHeaderData( 0, Qt::Horizontal, "#ID Operacion" );
    setHeaderData( 1, Qt::Horizontal, "#ID Orden Trabajo" );
    setHeaderData( 2, Qt::Horizontal, "Fecha de operacion" );
    setHeaderData( 3, Qt::Horizontal, "Descripcion" );
    setHeaderData( 4, Qt::Horizontal, "#tipo_operacion" );
    setHeaderData( 5, Qt::Horizontal, "#Tecnico" );
    setHeaderData( 6, Qt::Horizontal, "Costo" );
}
