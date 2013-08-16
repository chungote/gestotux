#include "mrecibosimpagos.h"

MRecibosImpagos::MRecibosImpagos(QObject *parent) :
QSqlTableModel(parent)
{
    setTable( "v_recibos_impagos" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "#Serie" );
    setHeaderData( 2, Qt::Horizontal, "Destinatario" );
    setHeaderData( 3, Qt::Horizontal, "Fecha emision" );
    setHeaderData( 4, Qt::Horizontal, "Monto" );
    setHeaderData( 5, Qt::Horizontal, "Cancelado" );
}
