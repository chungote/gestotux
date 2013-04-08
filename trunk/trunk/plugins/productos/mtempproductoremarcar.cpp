#include "mtempproductoremarcar.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMutableListIterator>

MTempProductoRemarcar::MTempProductoRemarcar( QObject *parent ) :
  QAbstractTableModel( parent )
{
  _id_productos = new QList<int>();
  _codigos = new QList<QString>();
  _nombres = new QList<QString>();
  _precio_original = new QList<double>();
  _sin_stock = new QList<bool>();
  _deshabilitado = new QList<bool>();

  _fijo = false;
  _porcentaje = false;
  _valor = 0.0;

  setHeaderData( 0, Qt::Horizontal, "#ID Producto" );
  setHeaderData( 1, Qt::Horizontal, "Código" );
  setHeaderData( 2, Qt::Horizontal, "Nombre del producto" );
  setHeaderData( 3, Qt::Horizontal, "Precio Original" );
  setHeaderData( 4, Qt::Horizontal, "Nuevo precio" );
}

void MTempProductoRemarcar::setearValorFijo( bool p )
{
  _fijo = p;
  _porcentaje = !p;
  emit dataChanged( index( 0, 3 ), index( rowCount(), 3 ) );
}

void MTempProductoRemarcar::setearPorcentaje( bool p )
{
  _fijo = !p;
  _porcentaje = p;
  emit dataChanged( index( 0, 3 ), index( rowCount(), 3 ) );
}

int MTempProductoRemarcar::columnCount( const QModelIndex & ) const
{ return 5; }

int MTempProductoRemarcar::rowCount( const QModelIndex & ) const
{ return _id_productos->size(); }

QVariant MTempProductoRemarcar::data(const QModelIndex &index, int role) const
{
    switch( role ) {
        case Qt::DisplayRole:
        {
            switch( index.column() ) {
                case 0: // #Id de producto
                {
                    return QString( "#%1" ).arg( _id_productos->at( index.row() ) );
                    break;
                }
                case 1: // Codigo del producto
                {
                    return QString( "%1" ).arg( _codigos->at( index.row() ) );
                    break;
                }
                case 2: // Nombre del producto
                {
                    return _nombres->at( index.row() );
                    break;
                }
                case 3: // Precio Original
                {
                    return QString( "$ %L1" ).arg( _precio_original->at( index.row() ), 10, 'f', 2 );
                    break;
                }
                case 4: // Precio Nuevo
                {
                    if( _porcentaje ) {
                        return QString( "$ %L1" ).arg( _precio_original->at( index.row() )*(_valor+1.0), 10, 'f', 2 );
                    } else if( _fijo ) {
                        return QString( "$ %L1" ).arg( _precio_original->at( index.row() )+_valor, 10, 'f', 2 );
                    }
                    break;
                }
                default:
                { break; }
            }
            break;
        }
        default:
        { break; }
    }
  return QVariant();
}


void MTempProductoRemarcar::agregarProducto( int id )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT id, codigo, nombre, precio_venta, habilitado, stock FROM producto WHERE id_producto = %1" ).arg( id ) ) ) {
        cola.next();
        beginInsertRows( QModelIndex(), rowCount(), rowCount() );
        int pos = rowCount();
        _id_productos->insert( pos, cola.record().value(0).toInt() );
        _codigos->insert( pos, cola.record().value(1).toString() );
        _nombres->insert( pos, cola.record().value(2).toString() );
        _precio_original->insert( pos, cola.record().value(3).toDouble() );
        _deshabilitado->insert( pos, !cola.record().value(4).toBool() );
        if( cola.record().value(5).toInt() > 0 ) {
            _sin_stock->insert( pos, false );
        } else {
            _sin_stock->insert( pos, true );
        }
        endInsertRows();
    } else {
        qWarning( "Error al consultar los datos del producto" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
}

void MTempProductoRemarcar::eliminarProducto( QModelIndex idx )
{
}

void MTempProductoRemarcar::cambioSinStock( bool estado )
{
    if( !estado )
        return;

    // Recorro la lista y elimino los elementos sin stock si existen
    for( int i = 0; i<_id_productos->size(); i++ ) {
        if( _sin_stock->at( i ) ) {

        }
    }
    return;
}

void MTempProductoRemarcar::cambioDeshabilitados( bool estado )
{
    if( !estado )
        return;

    // Recorro la lista y elimino los elementos sin stock si existen
    for( int i = 0; i<_id_productos->size(); i++ ) {
        if( _deshabilitado->at( i ) ) {

        }
    }
    return;
}

void MTempProductoRemarcar::cambioValor( double valor )
{
    _valor = valor;
    emit dataChanged( index( 0, 3 ), index( rowCount(), 3 ) );
}
