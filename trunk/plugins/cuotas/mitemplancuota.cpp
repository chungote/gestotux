#include "mitemplancuota.h"

#include <QSqlQuery>
#include <QSqlError>

MItemPlanCuota::MItemPlanCuota(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable( "item_cuota" );
    setHeaderData( 0, Qt::Horizontal, "#ID Item" );
    setHeaderData( 1, Qt::Horizontal, "#ID Plan" );
    setHeaderData( 2, Qt::Horizontal, "#Cuota" );
    setHeaderData( 3, Qt::Horizontal, "Importe" );
    setHeaderData( 4, Qt::Horizontal, "Fecha Vencimiento" );
    setHeaderData( 5, Qt::Horizontal, "Fecha de Pago" );
    setHeaderData( 6, Qt::Horizontal, "#ID pago" );
}

/*!
 * \fn MItemPlanCuota::agregarItem( int id_plan, int num_cuota, QDate fecha_venc, double importe )
 * Agrega un nuevo registro de item de cuota cuando se agrega un nuevo plan de cuota.
 * \param id_plan Identificador de relacion hacia el plan de cuotas.
 * \param num_cuota Numero de la cuota del plan.
 * \param fecha_venc Fecha desde la cual se empezará a pagar el plan.
 * \param importe Importe a pagar en esa cuota
 * \return Verdadero si se pudo agregar el item
 */
bool MItemPlanCuota::agregarItem(int id_plan, int num_cuota, QDate fecha_venc, double importe)
{
    QSqlQuery cola;
    if( !cola.prepare( "INSERT INTO item_cuota( id_plan, num_cuota, importe, fecha_venc ) VALUES (  :id_plan, :num_cuota, :importe, :fecha_venc )" ) ) {
        qDebug( "Error al preparar la cola para la inseción de los datos de un item de cuota" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return false;
    }
    cola.bindValue( ":id_plan", id_plan );
    cola.bindValue( ":num_cuota", num_cuota );
    cola.bindValue( ":importe", importe ),
    cola.bindValue( ":fecha_venc", fecha_venc );
    if( !cola.exec() ) {
        qDebug( "Error al ejecutar la cola de insersión de los datos de un item de cuota" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return false;
    } else {
        return true;
    }
    return false;
}
