#include "mgenerarcuotas.h"



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
    _clientes = new QHash<int,QPair<int,QString> >();
    _cuotas = new QHash<int, QPair<int,int> >();
    _importes = new QHash<int, double>();
    _comprobantes = new QHash<int, NumeroComprobante *>();
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
                  return _clientes->value( idx.row() ).second;
                  break;
              }
              case 3: // # Cuota ( 1/10 )
              {
                  return QString( "%1/%2" ).arg( _cuotas->value( idx.row() ).first ).arg( _cuotas->value( idx.row() ).second );
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
  return false;
}

int MGenerarCuotas::columnCount( const QModelIndex & ) const
{ return 6; }

int MGenerarCuotas::rowCount( const QModelIndex & ) const
{ return _cant; }


