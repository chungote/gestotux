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

MProductosTotales::MProductosTotales(QObject *parent)
 : QAbstractTableModel(parent)
{
 // Inicializo los sistemas
 Total = 0;
 //_id_listaPrecio = -1;
 _calcularTotal = false;
 _buscarPrecio = false;
 cantidades = new QHash<int, double>();
 precio_unitario = new QHash<int, double>();
 subtotales = new QHash<int, double>();
 productos = new QHash<int, int>();
 prods = new QMap<int, QString>();
 QSqlQuery cola( "SELECT nombre, id FROM producto" );
 while( cola.next() )
 {
        prods->insert( cola.record().value( "id" ).toInt(), cola.record().value("nombre").toString() );
 }
 cantidades->clear();
}


MProductosTotales::~MProductosTotales()
{}


bool MProductosTotales::insertRow(int row, const QModelIndex& parent)
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

bool MProductosTotales::removeRow(int row, const QModelIndex& parent)
{
  beginRemoveRows( parent, row, row );
  productos->remove( row );
  precio_unitario->remove( row );
  cantidades->remove( row );
  subtotales->remove( row );
  recalcularTotal();
  endRemoveRows();
  emit dataChanged( this->index( this->rowCount(), 1 ), this->index( this->rowCount(), 3 ) );
  return true;
}

bool MProductosTotales::setData(const QModelIndex& index, const QVariant& value, int role)
{
 if( !index.isValid() )
 {
   //qDebug( QString( "Indice invalido Dueños: col=%1, row=%2, role=%3").arg( index.column() ).arg( index.row() ).arg( role ).toLocal8Bit() );
   return false;
 }
 switch( role )
 {
        case Qt::EditRole:
        {
                switch( index.column() )
                {
                        // Producto
                        case 0:
                        {
                                //qDebug( qPrintable( QString( "insert: size: %1, index.row(): %2" ).arg( this->productos->size() ).arg( index.row() ) ) );
                                productos->insert( index.row(), value.toInt()  );
                                if( _buscarPrecio )
                                {
                                        // Busco el precio de venta este producto
                                        this->setData( this->index( index.row(), 1 ), QVariant::fromValue( buscarPrecioVenta( value.toInt() ) ), Qt::EditRole );
                                        //qDebug( qPrintable( QString( "buscando precio para id: %1 en row %2" ).arg( value.toInt() ).arg( index.row() ) ) );
                                }
                                break;
                        }
                        // Precio Unitario
                        case 1:
                        {
                                precio_unitario->insert( index.row(), value.toDouble() );
                                if( _calcularTotal )
                                {
                                        subtotales->insert( index.row(), cantidades->value( index.row() ) * value.toDouble() );
                                        recalcularTotal();
                                }
                                emit dataChanged( index , this->index( index.row(), 3 ) );
                                break;
                        }
                        // Cantidad
                        case 2:
                        {
                                // Veo si tengo que verificar el maximo posible
                                if( preferencias::getInstancia()->value( "Preferencias/Productos/Stock/limitar" ).toBool() )
                                {
                                        // Busco si el stock actual menos la cantidad es <= 0
                                        if( ( MProductos::stock( productos->value( index.row() ) ) - value.toDouble() ) <= 0 )
                                        {
                                                qWarning( "No hay suficientes unidades del producto para vender la cantidad pedida" );
                                                return false;
                                        }
                                }
                                cantidades->insert( index.row(), value.toDouble() );
                                if( _calcularTotal )
                                {
                                        subtotales->insert( index.row(), precio_unitario->value( index.row() ) * value.toDouble() );
                                        recalcularTotal();
                                }
                                emit dataChanged( index , this->index( index.row(), 3) );
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

int MProductosTotales::columnCount(const QModelIndex& parent) const
{
 if( _calcularTotal )
 { return 4; }
 else
 { return 3; }
}

int MProductosTotales::rowCount(const QModelIndex& parent) const
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
  if( index.column() == 3 )
  { return QFlags<Qt::ItemFlag>(!Qt::ItemIsEditable |  Qt::ItemIsSelectable ); }
  else
  { return QAbstractTableModel::flags( index ) | Qt::ItemIsEditable; }
 }
}

QVariant MProductosTotales::data(const QModelIndex& idx, int role) const
{
  if( !idx.isValid() )
  {
   //qDebug( QString( "Indice invalido Dueños: col=%1, row=%2, role=%3").arg( idx.column() ).arg( idx.row() ).arg( role ).toLocal8Bit() );
   return( QVariant() );
  }
 if( idx.row() == this->productos->size() && _calcularTotal )
 {
  //qDebug( qPrintable( QString::number( this->productos->size() ) ) );
  switch( idx.column() )
  {
        case 0:
        {
                if( role == Qt::DisplayRole )
                {
                        return "Cant:";
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
                if( role == Qt::DisplayRole )
                {
                        return QString( "$ %L1" ).arg( Total );
                }
                else if( role == Qt::TextAlignmentRole )
                {
                        return int( Qt::AlignRight | Qt::AlignVCenter );
                }
                else
                { return QVariant(); }
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
                        // Producto
                        case 0:
                        {
                                return prods->value( productos->value( idx.row() ) );
                                break;
                        }
                        // precio unitario
                        case 1:
                        {
                                return QString( "$ %L1" ).arg( precio_unitario->value( idx.row() ) );
                                break;
                        }
                        // Cantidades
                        case 2:
                        {
                                // Busco si existe
                                return QString( "%L1" ).arg( cantidades->value( idx.row() ) );
                                break;
                        }
                        // Subtotal
                        case 3:
                        {
                                return QString( "$ %L1" ).arg( subtotales->value( idx.row() ) );
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
                        case 1:
                        case 3:
                        {
                                return QColor(Qt::blue);
                                break;
                        }
                        case 2:
                        {
                                return QColor(Qt::green);
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
                        //Producto
                        case 0:
                        {
                                // tengo que devolver el Id de producto
                                return productos->value( idx.row() );
                                break;
                        }
                        // precio unitario
                        case 1:
                        {
                                return precio_unitario->value( idx.row() );
                                break;
                        }
                        // Cantidad
                        case 2:
                        {
                                return cantidades->value( idx.row() );
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
                        case 2:
                        case 1:
                        {
                                return int( Qt::AlignHCenter | Qt::AlignVCenter );
                                break;
                        }
                        case 0:
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
{
 return Total;
}


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
        { return "Producto"; break; }
        case 1:
        { return "Precio Unitario"; break; }
        case 2:
        { return "Cantidad"; break; }
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
    \fn MProductosTotales::buscarPrecioVenta( int id_producto )
 */
double MProductosTotales::buscarPrecioVenta( int id_producto )
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT precio_costo FROM producto WHERE id = %1" ).arg( id_producto ) ) )
 {
  cola.next();
 // qDebug( qPrintable( cola.lastQuery() ) );
  double precio = cola.record().value( 0 ).toDouble();
  //qDebug( "Precio encontrado" );
  double __recargo = preferencias::getInstancia()->value( "Preferencias/Ventas/ganancia", 10.00 ).toDouble();
  return precio * ( 1 + (__recargo/100) );
 }
 else
 {
  qDebug( "No se encontro el precio" );
  return 0.0;
 }
}
