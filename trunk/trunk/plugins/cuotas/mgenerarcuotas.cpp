#include "mgenerarcuotas.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDate>

MGenerarCuotas::MGenerarCuotas( QObject *parent )
{
    setHeaderData( 0, Qt::Horizontal, "#Num" );
    setHeaderData( 1, Qt::Horizontal, "#Plan" );
    setHeaderData( 2, Qt::Horizontal, "Cliente" );
    setHeaderData( 3, Qt::Horizontal, "#Cuota" );
    setHeaderData( 4, Qt::Horizontal, "Importe" );
    setHeaderData( 5, Qt::Horizontal, "#Recibo" );

    _numeros = new QHash<int, int>();
    _planes = new QHash<int, int>();
    _clientes = new QHash<int, QString>();
    _clientes_id = new QHash<int, int>();
    _cuotas = new QHash<int, QString>();
    _importes = new QHash<int, double>();
    _comprobantes = new QHash<int, NumeroComprobante *>();

    _total = 0.0;
    _cant = 0;
}

QVariant MGenerarCuotas::data( const QModelIndex &idx, int role ) const
{
    switch( role ) {
      case Qt::DisplayRole:
      {
          switch( idx.column() ) {
              case 0:
              {
                return QString( "#%1" ).arg( _numeros->value( idx.row() ) );
                break;
              }
              case 1:
              {
                return QString( "#%1" ).arg( _planes->value( idx.row() ) );
                  break;
              }
              case 2: // Nombre del cliente
              {
                  return _clientes->value( idx.row() );
                  break;
              }
              case 3: // # Cuota ( 1/10 )
              {
                  return _cuotas->value( idx.row() );
                  break;
              }
              case 4: // Importe de la cuota
              {
                  return QString( "$ %L1" ).arg( _importes->value( idx.row() ), 0, 'f', 10 );
                  break;
              }
              case 5:
              {
                  return _comprobantes->value( idx.row() )->aCadena();
                  break;
              }
              default:
              {
                return QVariant();
                break;
              }
          }
          break;
      }
      default:
      {
          return QVariant();
          break;
      }
    }
}

bool MGenerarCuotas::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if( role == Qt::EditRole ) {
        switch( index.column() ) {
            case 0:
            {
                // Esto se debe llamar si la fila no existe
                if( _numeros->contains( index.row() ) ) {
                    return false;
                } else {
                    _numeros->insert( index.row(), value.toInt() );
                    return true;
                }
                break;
            }
            case 1:
            {
                _planes->insert( index.row(), value.toInt() );
                return true;
                break;
            }
            case 2:
            {
                _cuotas->insert( index.row(), value.toString() );
            }

        }
    }
    return false;
}

int MGenerarCuotas::columnCount( const QModelIndex & ) const
{ return 6; }

int MGenerarCuotas::rowCount( const QModelIndex & ) const
{ return _cant; }

bool MGenerarCuotas::calcularComprobantes()
{
   _cant = 0;
   _total = 0.0;
   // Fecha del mes actual - Inicio del mes
   QDate fin_mes = QDate::currentDate();
   fin_mes.addDays( fin_mes.daysInMonth()-fin_mes.day() );
   QSqlQuery cola;
   if( cola.exec( QString( " SELECT ic.id_item_cuota, ic.id_plan_cuota, ic.num_cuota, pc.cantidad_cuotas, ic.monto, c.razon_social "
                           " FROM item_cuota AS ic "
                           "      INNER JOIN plan_cuota AS pc ON ic.id_plan_cuota = pc.id_plan_cuota "
                           "      INNER JOIN factura AS f ON pc.id_factura = f.id_factura "
                           "      INNER JOIN clientes AS c ON f.id_cliente = c.id "
                           " WHERE ic.fecha_pago IS NULL "
                           "   AND ic.id_recibo  IS NULL "
                           "   AND ic.fecha_vencimiento <= Datetime('%1') "
                           " GROUP BY ic.id_plan_cuota   "
                           " HAVING MIN( ic.num_cuota )  "
                           " ORDER BY ic.id_plan_cuota, ic.num_cuota " ).arg( fin_mes.toString( Qt::ISODate ) ) ) ){
       while( cola.next() ) {
           setData( index( _cant, 0 ), _cant, Qt::EditRole );
           setData( index( _cant, 1 ), cola.record().value( "id_plan_cuota" ).toInt()   , Qt::EditRole );
           setData( index( _cant, 2 ), QString( "%1/%2" ).arg( cola.record().value( "cantidad_cuotas" ).toInt(), cola.record().value("num_cuota").toInt() ), Qt::EditRole );
           setData( index( _cant, 2 ), cola.record().value( "razon_social"  ).toString(), Qt::EditRole );
           setData( index( _cant, 3 ), cola.record().value( "num_cuota"     ).toInt()   , Qt::EditRole );
           double monto = cola.record().value( "monto" ).toDouble();
           _total += monto;
           setData( index( _cant, 4 ), monto, Qt::EditRole );
           _cant++;
       }
       if( _cant > 0 ) {
           emit cambioTotal( _total );
           emit cambioCantidad( _cant );
           return true;
       } else {
           return false;
       }
   } else {
       qDebug( "Error al ejecutar la cola de averiguamiento de los datos de las cuotas a pagar" );
       qDebug( cola.lastError().text().toLocal8Bit() );
       qDebug( cola.lastQuery().toLocal8Bit() );
   }
   return false;
}

