#include "mtempproductoremarcar.h"

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
{
  return 4;
}

int MTempProductoRemarcar::rowCount( const QModelIndex & ) const
{
  return _id_productos->size();
}

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
}

void MTempProductoRemarcar::eliminarProducto( QModelIndex idx )
{
}

void MTempProductoRemarcar::cambioSinStock( bool estado )
{
    if( !estado )
        return;


}

void MTempProductoRemarcar::cambioDeshabilitados( bool estado )
{
    if( !estado )
        return;


}

void MTempProductoRemarcar::cambioValor( double valor )
{
    _valor = valor;
    emit dataChanged( index( 0, 3 ), index( rowCount(), 3 ) );
}
