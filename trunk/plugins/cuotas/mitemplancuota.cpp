#include "mitemplancuota.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

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

/**
 * @brief MItemPlanCuota::obtenerProximoImporte
 * Devuelve el importe del item de cuota que no esté pagado.
 * @param id_plan Identificador del plan
 * @return valor de la cuota
 */
double MItemPlanCuota::obtenerProximoImporte( const int id_plan )
{
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT monto FROM item_cuota WHERE id_plan_cuota = %1 AND fecha_pago is NULL ORDER BY fecha_vencimiento LIMIT 1" ).arg( id_plan ) ) ) {
      if( cola.next() ) {
          return cola.record().value(0).toDouble();
      } else {
          qDebug( "Error al hacer next en la cola de averiguacion del importe de un item de cuota" );
          qDebug( cola.lastError().text().toLocal8Bit() );
          qDebug( cola.lastQuery().toLocal8Bit() );
      }
  } else {
      qDebug( "Error al ejecutar la cola de averiguacion del importe de un item de cuota" );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
  }
  return -1.0;
}

/**
 * @brief MItemPlanCuota::obtenerIdProximaCuota
 * Busca el ID del proximo item de cuota a pagar para un plan específico
 * @param id_plan Identificador del plan
 * @return Identificador o -1 si hubo error o -2 si no existe proximo ítem
 */
int MItemPlanCuota::obtenerIdProximaCuota( const int id_plan )
{
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT id_item_cuota FROM item_cuota WHERE id_plan_cuota = %1 AND fecha_pago is NULL ORDER BY fecha_vencimiento LIMIT 1" ).arg( id_plan ) ) ) {
      if( cola.next() ) {
          return cola.record().value(0).toInt();
      } else {
          qDebug( "Error al hacer next en la cola de averiguacion del id de un item de cuota" );
          qDebug( cola.lastError().text().toLocal8Bit() );
          qDebug( cola.lastQuery().toLocal8Bit() );
          return -2;
      }
  } else {
      qDebug( "Error al ejecutar la cola de averiguacion del id de un item de cuota" );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
  }
  return -1.0;
}

/**
 * @brief MItemPlanCuota::buscarReciboEmitido
 * @param id_plan Identificador del plan
 * @return Identificador del recibo si existe, -2 si no se encuentra el dato y -1 si hubo un error
 */
int MItemPlanCuota::buscarReciboEmitido( const int id_plan )
{
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT id_recibo FROM item_cuota WHERE id_plan_cuota = %1 AND fecha_pago is NULL ORDER BY fecha_vencimiento LIMIT 1" ).arg( id_plan ) ) ) {
      if( cola.next() ) {
          return cola.record().value(0).toInt();
      } else {
          qDebug( "Error al hacer next en la cola de averiguacion del id de recibo de un item de cuota" );
          qDebug( cola.lastError().text().toLocal8Bit() );
          qDebug( cola.lastQuery().toLocal8Bit() );
          return -2;
      }
  } else {
      qDebug( "Error al ejecutar la cola de averiguacion del id de recibo de un item de cuota" );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
  }
  return -1;
}

/**
 * @brief MItemPlanCuota::setearItemCuotaPagadoSegunRecibo
 * Setea un plan de cuota como pagado según el recibo pagado
 * @param id_recibo Identificador de recibo
 * @return Verdadero si se pudo setear, falso en caso contrario
 */
bool MItemPlanCuota::setearItemCuotaPagadoSegunRecibo( const int id_recibo, QDateTime fecha_pagado )
{
  QSqlQuery cola;
  if( cola.exec( QString( "UPDATE item_cuota SET fecha_pagado = %2 WHERE id_recibo = %1 AND fecha_pago is NULL" ).arg( id_recibo ).arg( fecha_pagado.toString( Qt::ISODate ) ) ) ) {
      return true;
  } else {
      qDebug( "Error al ejecutar la cola de seteo de item de cuota pagado según id de recibo " );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
  }
  return false;
}

/**
 * @brief MItemPlanCuota::buscarSiReciboAPagar
 * Verifica si el identificador de recibo se encuentra en un item de cuota a pagar
 * @param id_recibo Identificador del recibo
 * @return verdader si corresponde a una cuota o falso.
 */
bool MItemPlanCuota::buscarSiReciboAPagar( const int id_recibo )
{
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT COUNT( id_recibo ) FROM item_cuota WHERE id_recibo = %1 AND fecha_pago is NULL" ).arg( id_recibo ) ) ) {
      if( cola.next() ) {
          if ( cola.record().value(0).toInt() > 0 ) {
              return true;
          }
      } else {
          qDebug( "Error al hacer next en la cola de averiguacion del id de recibo a pagar de un item de cuota" );
          qDebug( cola.lastError().text().toLocal8Bit() );
          qDebug( cola.lastQuery().toLocal8Bit() );
      }
  } else {
      qDebug( "Error al ejecutar la cola de averiguacion del id de recibo a pagar de un item de cuota" );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
  }
  return false;
}

/**
 * @brief MItemPlanCuota::setearItemCuotaPagado
 * Setea el item de cuota como pagado con el identificador de recibo
 * @param id_item_cuota Identificador de item de cuota
 * @param id_recibo Identificador del recibo que paga la cuota.
 * @return Verdadero si se pudo hacer la asociacion.
 */
bool MItemPlanCuota::setearItemCuotaPagado( const int id_item_cuota, const int id_recibo, QDateTime fecha_pagado )
{
  QSqlQuery cola;
  if( cola.exec( QString( "UPDATE item_cuota SET fecha_pagado = %2, id_recibo = %1, WHERE id_item_cuota = %3" ).arg( id_recibo ).arg( fecha_pagado.toString( Qt::ISODate ) ).arg( id_item_cuota ) ) ) {
      return true;
  } else {
      qDebug( "Error al ejecutar la cola de seteo de item de cuota pagado" );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
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
