#include "mtempproductoremarcar.h"

MTempProductoRemarcar::MTempProductoRemarcar(QObject *parent) :
  QAbstractTableModel(parent)
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
}

void MTempProductoRemarcar::cambioDeshabilitados( bool estado )
{
}

void MTempProductoRemarcar::cambioValor( double valor )
{
}
