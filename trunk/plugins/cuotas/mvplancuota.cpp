#include "mvplancuota.h"

MVPlanCuota::MVPlanCuota(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable( "v_plan_cuota" );
    setHeaderData( 0, Qt::Horizontal, "#Plan" );
    setHeaderData( 1, Qt::Horizontal, "Cliente" );
    setHeaderData( 2, Qt::Horizontal, "Progreso" );
    setHeaderData( 3, Qt::Horizontal, "Faltante" );
    setHeaderData( 4, Qt::Horizontal, "Ultimo Pago" );
    setHeaderData( 5, Qt::Horizontal, "Proximo Pago" );
}
