#include "mvpagos.h"
#include "mpagos.h"

MVPagos::MVPagos(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable( "v_recibos" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "#Serie" );
    setHeaderData( 2, Qt::Horizontal, "Destinatario" );
    setHeaderData( 3, Qt::Horizontal, "Fecha emision" );
    setHeaderData( 4, Qt::Horizontal, "Monto" );
    setHeaderData( 5, Qt::Horizontal, "Forma de pago" );
    setHeaderData( 6, Qt::Horizontal, "Pagado" );
    setHeaderData( 7, Qt::Horizontal, "Cancelado" );
}


QVariant MVPagos::data(const QModelIndex& item, int role) const
{
 switch( role )
 {
  case Qt::DisplayRole:
  {
   switch( item.column() )
   {
     case 3: // fecha de pago
     { return QSqlRelationalTableModel::data( item, role ).toDate().toString( Qt::LocalDate ); break; }
     case 4: // Monto
     { return QString::number( QSqlRelationalTableModel::data( item, role ).toDouble(), 'f', 2 ).prepend( "$  "); break; }
     case 5:
     {
       switch( QSqlRelationalTableModel::data( item, role ).toInt() )
       {
        case MPagos::SinPagar:
        { return "Sin Pagar"; break; }
        case MPagos::Efectivo:
        { return "Efectivo"; break; }
        case MPagos::Otro:
        { return "Otro"; break; }
       }
       break;
     }
     case 6: // Cancelado ( anulado ) y pagado
     case 7:
     //{ return QSqlRelationalTableModel::data( item, role ).toBool(); break; }
     {
             if( QSqlRelationalTableModel::data( item, role ).toBool() ) {
                return "Si";
             } else {
                return "No";
             }
             break;
     }
     default:
     { return QSqlRelationalTableModel::data( item, role ); break; }
   }
   break;
  }
  case Qt::EditRole:
  {
     switch( item.column() ) {
        case 6:
        case 7:
        { return QSqlRelationalTableModel::data( item, role ).toBool(); break; }
        default:
        { return QSqlRelationalTableModel::data( item, role ); break; }
     }
     break;
  }
  case Qt::TextAlignmentRole:
  {
   switch( item.column() )
   {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    { return int( Qt::AlignCenter | Qt::AlignVCenter ); break; }
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
 return QSqlRelationalTableModel::data(item, role);
}