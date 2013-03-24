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
    if( !cola.prepare( "INSERT INTO item_cuota( id_plan_cuota, num_cuota, monto, fecha_vencimiento ) VALUES (  :id_plan_cuota, :num_cuota, :monto, :fecha_vencimiento )" ) ) {
        qDebug( "Error al preparar la cola para la inseción de los datos de un item de cuota" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return false;
    }
    cola.bindValue( ":id_plan_cuota", id_plan );
    cola.bindValue( ":num_cuota", num_cuota );
    cola.bindValue( ":monto", importe ),
    cola.bindValue( ":fecha_vencimiento", fecha_venc );
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

QVariant MItemPlanCuota::data(const QModelIndex &item, int role) const
{
    if( item.isValid() ) {
        switch( item.column() ) {
            case 0: // Identificador del item del plan de cuota
            case 1: // Identificador del plan de cuota padre
            case 2: // Numero de cuota
            {
                switch( role ) {
                    case Qt::DisplayRole:
                    { return QString( "#%1").arg( QSqlRelationalTableModel::data( item, role ).toInt() ); break; }
                    case Qt::EditRole:
                    { return QSqlRelationalTableModel::data( item, role ).toInt(); break; }
                    default:
                    { return QSqlRelationalTableModel::data( item, role ); break; }
                }
                break;
            }
            case 3: // Importe
            {
                switch( role ) {
                    case Qt::DisplayRole:
                    { return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( item, role ).toDouble(), 10, 'f', 2 ); break; }
                    case Qt::EditRole:
                    { return QSqlRelationalTableModel::data( item, role ).toDouble(); break; }
                    default:
                    { return QSqlRelationalTableModel::data( item, role ); break; }
                }
                break;
            }
            case 4: // Fecha de vencimiento
            case 5: // Fecha de Pago
            {
                switch( role ) {
                    case Qt::DisplayRole:
                    { return QSqlRelationalTableModel::data( item, role ).toDate().toString(); break; }
                    case Qt::EditRole:
                    { return QSqlRelationalTableModel::data( item, role ).toDate(); break; }
                    default:
                    { return QSqlRelationalTableModel::data( item, role ); break; }
                }
                break;
            }
            default:
            {
                return QSqlRelationalTableModel::data( item, role );
                break;
            }
        }
    } else {
        return QVariant();
    }
}
