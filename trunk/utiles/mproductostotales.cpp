/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "mproductostotales.h"

#include "../plugins/productos/mproductos.h"

#include "preferencias.h"

#include <QColor>
#include <QSize>
#include <QSqlQuery>
#include <QSqlRecord>

MProductosTotales::MProductosTotales( QObject *parent, QMap<int, QString> *_mapa_id_prod )
 : QAbstractTableModel(parent)
{
 // Inicializo los sistemas
 Total = 0;
 _calcularTotal = false;
 _buscarPrecio = false;
 cantidades = new QHash<int, double>();
 precio_unitario = new QHash<int, double>();
 subtotales = new QHash<int, double>();
 productos = new QHash<int, int>();
 if( _mapa_id_prod != 0 )
    prods = _mapa_id_prod;
 cantidades->clear();
 _tipoPrecio = MProductosTotales::Venta;
 _admite_duplicados = false;
}


MProductosTotales::~MProductosTotales()
{
    delete cantidades;
    delete precio_unitario;
    delete subtotales;
    delete productos;
    cantidades = 0;
    precio_unitario = 0;
    subtotales = 0;
    productos = 0;
    prods = 0;
}

bool MProductosTotales::insertRow( int row, const QModelIndex& parent )
{
 if( row == -1 )
 { row = cantidades->size(); }
 beginInsertRows( parent, row, row );
 cantidades->insert( row, 0 );
 precio_unitario->insert( row, 0 );
 subtotales->insert( row, 0 );
 productos->insert( row, -1 );
 //qDebug( qPrintable( "Insertada fila: " + QString::number( row ) ) );
 endInsertRows();
 emit dataChanged( this->index( row, 0 ), this->index( row, 3 ) );
 emit dataChanged( this->index( this->rowCount(), 1 ), this->index( this->rowCount(), 3 ) );
 return true;
}

bool MProductosTotales::removeRow( int row, const QModelIndex& parent )
{
  //qDebug( QString( "Eliminando fila: %1" ).arg( row ).toLocal8Bit() );
  beginRemoveRows( parent, row, row );
  productos->remove( row );
  precio_unitario->remove( row );
  cantidades->remove( row );
  subtotales->remove( row );
  recalcularTotal();
  endRemoveRows();
  emit dataChanged( this->index( row, 0 ), this->index( this->rowCount(), 4 ) );
  return true;
}

bool MProductosTotales::setData(const QModelIndex& index, const QVariant& value, int role)
{
 if( !index.isValid() )
 {
   //qDebug( QString( "Indice invalido Due�os: col=%1, row=%2, role=%3").arg( index.column() ).arg( index.row() ).arg( role ).toLocal8Bit() );
   return false;
 }
 switch( role )
 {
        case Qt::EditRole:
        {
                switch( index.column() )
                {
                        // Cantidad
                        case 0:
                        {
                                // Veo si tengo que verificar el maximo posible y el producto es valido y no estamos en buscar precio de compra ( ingresando compra no controla stock )
                                if( preferencias::getInstancia()->value( "Preferencias/Productos/Stock/limitar" ).toBool() &&
                                        this->data( this->index( index.row(), 1 ), Qt::EditRole ).toInt() == 0 && _tipoPrecio != MProductosTotales::Costo )
                                {
                                        // Busco si el stock actual menos la cantidad es <= 0
                                        qDebug( QString( "Stock del producto: %1").arg( MProductos::stock( productos->value( index.row() ) ) ).toLocal8Bit() );
                                        if( ( MProductos::stock( productos->value( index.row() ) ) - value.toDouble() ) <= 0 )
                                        {
                                                qWarning( "No hay suficientes unidades del producto para vender la cantidad pedida" );
                                                qDebug( QString( "Stock del producto (cantidad): %1").arg( MProductos::stock( productos->value( index.row() ) ) ).toLocal8Bit() );
                                                return false;
                                        }
                                }
                                cantidades->insert( index.row(), value.toDouble() );
                                if( _calcularTotal )
                                {
                                        subtotales->insert( index.row(), precio_unitario->value( index.row() ) * value.toDouble() );
                                        recalcularTotal();
                                }
                                emit dataChanged( index , this->index( index.row(), 3 ) );
                                return true;
                                break;
                        }
                        // Producto
                        case 1:
                        {
                                //qDebug( qPrintable( QString( "insert: size: %1, index.row(): %2" ).arg( this->productos->size() ).arg( index.row() ) ) );
                                if( !value.isValid() ) { qDebug( "El valor es invalido!" ); return false; }
                                if( !prods->contains( value.toInt() ) ) {
                                    qDebug( "Indice no encontrado en la lista de productos" );
                                    return false;
                                }
                                // Veo si tengo que verificar el maximo posible en stock, el producto es valido o estamos en modo compra
                                if( preferencias::getInstancia()->value( "Preferencias/Productos/Stock/limitar" ).toBool()  && this->data( this->index( index.row(), 1 ), Qt::EditRole ).toInt() == 0 && _tipoPrecio != MProductosTotales::Costo)
                                {
                                        // Busco si el stock actual menos la cantidad es <= 0
                                        if( ( MProductos::stock( productos->value( index.row() ) ) - this->data( this->index( index.row(), 0 ), Qt::EditRole ).toDouble() ) <= 0 )
                                        {
                                                qWarning( "No hay suficientes unidades del producto para vender la cantidad pedida" );
                                                qDebug( QString( "Stock del producto(producto): %1").arg( MProductos::stock( productos->value( index.row() ) ) ).toLocal8Bit() );
                                                return false;
                                        }
                                }
                                productos->insert( index.row(), value.toInt() );
                                //qDebug( QString( "Valor insertado en productos %1!").arg( value.toInt() ).toLocal8Bit() );
                                if( _buscarPrecio && value.toInt() > 0 )
                                {
                                        // Busco el precio de venta este producto
                                        double precio = 0.0;
                                        if( this->_tipoPrecio ==  MProductosTotales::Costo ) {
                                                precio = buscarPrecioVenta( value.toInt() );
                                        } else if( this->_tipoPrecio == MProductosTotales::Venta ){
                                                precio = buscarPrecioCompra( value.toInt() );
                                        }
                                        this->setData( this->index( index.row(), 2 ), QVariant::fromValue( precio ), Qt::EditRole );
                                        //qDebug( qPrintable( QString( "buscando precio para id: %1 en row %2" ).arg( value.toInt() ).arg( index.row() ) ) );
                                }
                                return true;
                                break;
                        }
                        // Precio Unitario
                        case 2:
                        {
                                precio_unitario->insert( index.row(), value.toDouble() );
                                if( _calcularTotal )
                                {
                                        subtotales->insert( index.row(), cantidades->value( index.row() ) * value.toDouble() );
                                        recalcularTotal();
                                }
                                emit dataChanged( index , this->index( index.row(), 3 ) );
                                return true;
                                break;
                        }

                        // Subtotal
                        case 3:
                        {
                                return true;
                        }
                        default:
                        {
                                return false;
                        }
                }
                break;
        }
        default:
        { return false; break; }
  }
}

int MProductosTotales::columnCount(const QModelIndex& /*parent*/) const
{
 if( _calcularTotal )
 { return 4; }
 else
 { return 3; }
}

int MProductosTotales::rowCount(const QModelIndex& /*parent*/) const
{
 if( _calcularTotal )
 { return productos->size() + 1; }
 else
 { return productos->size(); }
}

Qt::ItemFlags MProductosTotales::flags(const QModelIndex& index) const
{
 if( index.row() >= this->productos->size() )
 {
  return QFlags<Qt::ItemFlag>(!Qt::ItemIsSelectable | !Qt::ItemIsEditable | Qt::ItemIsEnabled );
 }
 else
 {
  if( index.column() == 3  || index.column() == 1 )
  { return QFlags<Qt::ItemFlag>(!Qt::ItemIsEditable |  Qt::ItemIsSelectable ); }
  else
  { return QAbstractTableModel::flags( index ) | Qt::ItemIsEditable; }
 }
}

QVariant MProductosTotales::data(const QModelIndex& idx, int role) const
{
  if( !idx.isValid() )
  { return( QVariant() ); }
 if( idx.row() == this->productos->size() && _calcularTotal )
 {
  //qDebug( qPrintable( QString::number( this->productos->size() ) ) );
  switch( idx.column() )
  {
        case 0:
        {
                if( role == Qt::DisplayRole )
                {
                    return "Cantidad de lineas:";
                } else if( role == Qt::TextAlignmentRole ) {
                    return int( Qt::AlignRight | Qt::AlignVCenter );
                } else {
                    return QVariant();
                }
                break;
        }
        case 1:
        {
                if( role == Qt::DisplayRole )
                {
                        return QString( "%L1" ).arg( this->productos->size() );
                }
                else if( role == Qt::TextAlignmentRole )
                {
                    return int( Qt::AlignVCenter | Qt::AlignHCenter );
                }
                else
                { return QVariant(); }
                break;
        }
        case 2:
        {
                if( role == Qt::DisplayRole )
                {
                    return "Total:";
                } else if( role == Qt::TextAlignmentRole ) {
                    return int( Qt::AlignRight | Qt::AlignVCenter );
                } else {
                    return QVariant();
                }
                break;
        }
        case 3:
        {
                if( role == Qt::DisplayRole ) {
                    return QString( "$ %L1" ).arg( Total, 10, 'f', 2 );
                } else if( role == Qt::TextAlignmentRole ) {
                    return int( Qt::AlignRight | Qt::AlignVCenter );
                } else {
                    return QVariant();
                }
                break;
        }
        default:
        {
                return QVariant();
                break;
        }
  }
 } // Fin ultima fila
 else
 {

 switch( role )
 {
        case Qt::DisplayRole:
        {
                switch( idx.column() )
                {
                        // Cantidades
                        case 0:
                        {
                                return QString( "%L1" ).arg( cantidades->value( idx.row() ) );
                                break;
                        }
                        // Producto
                        case 1:
                        {
                                // Devuelvo el mapeo idfila->productos->prods
                                if( prods->contains( productos->value( idx.row() ) ) ) {
                                    return prods->value( productos->value( idx.row() ) );
                                } else {
                                    qDebug( QString( "No se encontro el articulo en el data. Row=%1, indice=%2 " ).arg( idx.row() ).arg( productos->value( idx.row()) ).toLocal8Bit() );
                                    return " error al buscar el prod en prods ";
                                }
                                break;
                        }
                        // precio unitario
                        case 2:
                        {
                                return QString( "$ %L1" ).arg( precio_unitario->value( idx.row() ), 10, 'f', 2 );
                                break;
                        }

                        // Subtotal
                        case 3:
                        {
                                return QString( "$ %L1" ).arg( subtotales->value( idx.row() ), 10, 'f', 2 );
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
        case Qt::TextColorRole:
        {
                switch ( idx.column() )
                {
                        case 0:
                        {
                                return QColor(Qt::blue);
                                break;
                        }
                        default:
                        {
                                return QColor(Qt::black);
                                break;
                        }
                }
                break;
        }
        case Qt::EditRole:
        {
                switch( idx.column() )
                {
                        // Cantidad
                        case 0:
                        {
                                return cantidades->value( idx.row() );
                                break;
                        }
                        //Producto
                        case 1:
                        {
                                // tengo que devolver el Id de producto de la lista de general
                                return productos->value( idx.row() );
                                // Si el item no existe, devuelve cero....esto proboca que no se verifique el stock si esta habilitado
                                break;
                        }
                        // precio unitario
                        case 2:
                        {
                                return precio_unitario->value( idx.row() );
                                break;
                        }

                        default:
                        {
                                return false;
                                break;
                        }
                }
                break;
        }
        case Qt::TextAlignmentRole:
        {
                switch ( idx.column() )
                {
                        case 0:
                        case 2:
                        {
                                return int( Qt::AlignHCenter | Qt::AlignVCenter );
                                break;
                        }
                        case 1:
                        {
                                return int( Qt::AlignLeft | Qt::AlignVCenter );
                                break;
                        }
                        default:
                        {
                                return int( Qt::AlignRight | Qt::AlignVCenter );
                                break;
                        }
                }
                break;
        }
        case Qt::ToolTipRole:
        case Qt::StatusTipRole:
        {
                return QVariant( "Haga doble click o seleccione y F2 para editar" );
                break;
        }
        default:
        { return QVariant(); break; }
 }
 }// Fin fila de total else
}

/*!
    \fn MProductosTotales::recalcularTotal()
 */
void MProductosTotales::recalcularTotal()
{
 Total = 0;
 for( QHash<int, double>::const_iterator i = subtotales->constBegin(); i != subtotales->constEnd(); ++i )
 {
  Total += i.value();
 }
 // Emito la señal de que cambio el valor
 emit dataChanged( this->index( this->cantidades->size(), 0 ), this->index( this->cantidades->size(), 3 ) );
}


/*!
    \fn MProductosTotales::total()
 */
double MProductosTotales::total()
{ return Total; }


/*!
    \fn MProductosTotales::headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const
 */
QVariant MProductosTotales::headerData ( int section, Qt::Orientation orientation, int role ) const
{
 if( orientation == Qt::Horizontal  &&  role == Qt::DisplayRole )
 {
  switch( section )
  {
        case 0:
        { return "Cantidad"; break; }
        case 1:
        { return "Producto"; break; }
        case 2:
        { return "Precio Unitario"; break; }
        case 3:
        { return "Subtotal"; break; }
        default:
        { return section; }
  }
 }
 else
 {
  return QAbstractTableModel::headerData( section, orientation, role );
 }
}


/*!
    \fn MProductosTotales::calcularTotales( bool sino  )
 */
void MProductosTotales::calcularTotales( bool sino  )
{ _calcularTotal = sino; }


/*!
    \fn MProductosTotales::buscaPrecios()
 */
bool MProductosTotales::buscaPrecios()
{ return _buscarPrecio; }


/*!
    \fn MProductosTotales::buscarPrecios( bool activado )
 */
void MProductosTotales::buscarPrecios( bool activado )
{ _buscarPrecio = activado; /*qDebug( "busqueda de precios activada" );*/ }

/*!
    \fn MProductosTotales::buscarPrecioCompra( int id_producto )
    Busca el precio de costo del producto
 */
double MProductosTotales::buscarPrecioCompra( int id_producto )
{
 if( id_producto > 0 ) {
     QSqlQuery cola;
     if( cola.exec( QString( "SELECT precio_costo FROM producto WHERE id = %1 LIMIT 1" ).arg( id_producto ) ) )
     {
      cola.next();
      return cola.record().value(0).toDouble();
     }
     else
     {
      qDebug( "No se encontro el precio de compra" );
      return 0.0;
     }
  } else {
      // El precio se va a ingresar a mano, porque no esta en la base de datos de productos
     return 0.0;
  }
}

/*!
    \fn MProductosTotales::buscarPrecioVenta( int id_producto )
    Busca el precio de costo del producto
 */
double MProductosTotales::buscarPrecioVenta( int id_producto )
{
 if( id_producto > 0 ) {
     QSqlQuery cola;
     if( cola.exec( QString( "SELECT precio_venta FROM producto WHERE id = %1 LIMIT 1" ).arg( id_producto ) ) )
     {
      cola.next();
      return cola.record().value(0).toDouble();
     }
     else
     {
      qDebug( "No se encontro el precio de compra" );
      return 0.0;
     }
  } else {
      // El precio se va a ingresar a mano, porque no esta en la base de datos de productos
     return 0.0;
  }
}

#include <QInputDialog>
void MProductosTotales::agregarNuevoProducto( int cantidad, int Id )
{
  // Veo si existe y lo agrego a la lista si no existe....
  bool ok = false;
  double precio_unitario = -1.1;

  if( Id <= -1 ) {
      // Pido el precio si fue agregado especificamente
      precio_unitario = QInputDialog::getDouble( 0, "Falta precio", "Ingrese el precio unitario", 0.0, 0.0, 2147483647, 2, &ok );
  } else {

      if( this->_buscarPrecio ) {
          if( this->_tipoPrecio == MProductosTotales::Costo ) {
            precio_unitario = buscarPrecioCompra( Id );
          } else {
            precio_unitario = buscarPrecioVenta( Id );
          }
          ok = true;
      } else {
          // Como no busca el precio, inserto el dialogo
          precio_unitario = QInputDialog::getDouble( 0, "Falta precio", "Ingrese el precio unitario", 0.0, 0.0, 2147483647, 2, &ok );
      }

      // Es un producto valido
      if( _tipoPrecio != MProductosTotales::Costo ) {
        if( ( MProductos::stock( Id ) - cantidad ) < 0 ) {
              qDebug( "-> Error, stock negativo" );
              qWarning( "-> El stock de este producto es insuficiente para la cantidad que intenta vender." );
              return;
        }
      }
  }

  // Inserto el dato con la cantidad si fue buscado el precio o insertado
  if( ok ) {
     // Verifico si no existe ya el producto
      if( !_admite_duplicados ) {
        //qWarning( "Buscando productos iguales" );
        // Busco si existe en la lista
          int pos = this->productos->values().indexOf( Id );
          if( pos != -1 ) {
              // El producto ya existe.... Solo actualizo la cantidad
              // Segun la documentacion this->productos->values() y this->productos->keys() tienen el mismo orden
              int id_fila = this->productos->keys().at( pos );
              double cant = this->cantidades->value( id_fila );
              double ncant = cant + cantidad;
              this->cantidades->insert( id_fila, ncant );
              this->subtotales->insert( id_fila, ncant * precio_unitario );

              // Actualizo el subtotal
              emit dataChanged( this->index( id_fila, 0 ), this->index( id_fila, this->columnCount() ) );

              if( _calcularTotal )
                  recalcularTotal();
                  emit dataChanged( this->index( this->rowCount(), 0 ), this->index( this->rowCount(), this->columnCount() )  );

              return;
          }
      }
    if( this->insertRow( -1 ) ) {

        int id_fila = this->rowCount()-1;

        if( _calcularTotal )
            id_fila--;

        this->cantidades->insert     ( id_fila, cantidad                   );
        this->productos->insert      ( id_fila, Id                         );
        this->precio_unitario->insert( id_fila, precio_unitario            );
        this->subtotales->insert     ( id_fila, precio_unitario * cantidad );

        recalcularTotal();

        emit dataChanged( this->index( id_fila, 0 ), this->index( id_fila, this->columnCount() ) );

        if( _calcularTotal )
            emit dataChanged( this->index( this->rowCount(), 0 ), this->index( this->rowCount(), this->columnCount() )  );

    } else {
        // error al insertar el articulo
        qDebug( "Error al insertar la fila al ingresar un producto nuevo" );
        return;
    }
  } else {
        // No quiso ingresar un precio unitario
      qDebug( "No quiso ingresar el precio unitario. No ingreso el producto" );
      return;
  }
  return;
}

void MProductosTotales::setearTipoPrecioBuscar( int t )
{
    if( t == MProductosTotales::Costo ) {
        this->_tipoPrecio = MProductosTotales::Costo;
    } else if( t == MProductosTotales::Venta ) {
        this->_tipoPrecio = MProductosTotales::Venta;
    }
}

int  MProductosTotales::tipoPrecioBuscar()
{ return this->_tipoPrecio; }

