/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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
#include "mcompraproductos.h"

#include <QHash>
#include <QColor>
#include <QSize>

MCompraProductos::MCompraProductos( QObject *parent, bool calcula )
 : QSqlRelationalTableModel(parent), Total(0.0)
{
 setTable( "compras_productos" );
 setHeaderData( 0, Qt::Horizontal, tr( "#ID" ) );
 setHeaderData( 1, Qt::Horizontal, tr( "#ID Compra" ) );
 setRelation( 1, QSqlRelation( "compras", "id", "id" ) );
 setHeaderData( 2, Qt::Horizontal, tr( "Producto" ) );
 setRelation( 2, QSqlRelation( "producto", "id", "nombre" ) );
 setHeaderData( 3, Qt::Horizontal, tr( "Precio" ) );
 setHeaderData( 4, Qt::Horizontal, tr( "Cantidad" ) );
 if( calcula == true )
 {
  calcularTotales();
  setHeaderData( 5, Qt::Horizontal, tr( "SubTotal" ) );
  subtotales = new QHash<int, double>();
  setEditStrategy( QSqlTableModel::OnManualSubmit );
  connect( this, SIGNAL( beforeDelete( int ) ), this, SLOT( eliminarFila( int ) ) );
 }
}


MCompraProductos::~MCompraProductos()
{
}



/*!
    \fn MCompraProductos::data(const QModelIndex& idx, int role) const
 */
QVariant MCompraProductos::data(const QModelIndex& idx, int role) const
{
  if( !idx.isValid() )
  {
   qDebug( QString( "Indice invalido Dueños: col=%1, row=%2, role=%3").arg( idx.column() ).arg( idx.row() ).arg( role ).toLocal8Bit() );
   return( QVariant() );
  }
 if( idx.row() >= QSqlRelationalTableModel::rowCount() )
 {
  switch( idx.column() )
  {
	case 2:
	{
		if( role != Qt::DisplayRole )
		{
			return QVariant();
		}
		return "Cant:";
		break;
	}
	case 3:
	{
		if( role != Qt::DisplayRole )
		{
			return QVariant();
		}
		return QString( "%L1" ).arg( QSqlRelationalTableModel::rowCount() );
		break;
	}
	case 4:
	{
		if( role != Qt::DisplayRole )
		{
			return QVariant();
		}
		return "Total:";
		break;
	}
	case 5:
	{
		if( role != Qt::DisplayRole )
		{ return QVariant(); }
		return QString( "$ %L1" ).arg( Total );
		break;
	}
	default:
	{
		return QVariant();
		break;
	}
  }
 }
  switch( role )
 {
	case Qt::DisplayRole:
	{
		switch( idx.column() )
		{
			// ID
			case 0:
			{
				return QSqlRelationalTableModel::data(idx, role).toString().prepend( "#" );
				break;
			}
			case 3:
			{
				return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data(idx, role).toDouble() );
				break;
			}
			case 5:
			{
				if( calculaTotales )
				{
					// Busco si existe
					if( subtotales->find( idx.row() ) != subtotales->end() )
					{
						return QString( "$ %L1" ).arg( subtotales->value( idx.row() ) );
					}
					else
					{
						// Calculo el valor
						double sub = data( index( idx.row(), 3 ), Qt::EditRole ).toDouble() * data( index( idx.row(), 4 ), Qt::EditRole ).toDouble();
 						subtotales->insert( idx.row(), sub );
						return QString( "$ %L1" ).arg( sub );
					}
				}
				else
				{
					return QVariant();
				}
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data(idx, role);
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
			case 4:
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
			case 2:
			{
				return QSqlTableModel::data( idx, role );
				break;
			}
			case 3:
			{
				return QSqlRelationalTableModel::data( idx, role ).toDouble();
				break;
			}
			case 4:
			{
				return QSqlRelationalTableModel::data( idx,role ).toInt();
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data( idx, role );
				break;
			}
		}
		break;
	}
	case Qt::SizeHintRole:
	{
	       switch( idx.column() )
	       {
	         case 3:
	         {
	           QSize tam = QSqlRelationalTableModel::data( idx, Qt::SizeHintRole ).toSize();
	           tam.setWidth( tam.width() + 110 );
	           return tam;
	           break;
	         }
	         default:
	         {
	          return QSqlRelationalTableModel::data( idx, role );
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
			case 4:
			{
				return int( Qt::AlignHCenter | Qt::AlignVCenter );
				break;
			}
			case 2:
			case 5:
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
	case Qt::CheckStateRole:
	{
		return QSqlRelationalTableModel::data( idx, role );
		break;
	}
	case Qt::ToolTipRole:
	case Qt::StatusTipRole:
	{
		return QVariant( "Haga doble click o seleccione y F2 para editar" );
		break;
	}
	default:
	{
		return QSqlRelationalTableModel::data( idx, role);
		break;
	}
 }
}


/*!
    \fn MCompraProductos::calcularTotales()
 */
void MCompraProductos::calcularTotales()
{
  calculaTotales = true;
//   qDebug( "Seteado modelo para calculo de totales y subtotales" );
}


/*!
    \fn MCompraProductos::total()
	Devuelve el total de la lista
 */
double MCompraProductos::total()
{
 return Total;
}


/*!
    \fn MCompraProductos::index( int row, int column, const QModelIndex & parent = QModelIndex() ) const
	Genera los indices propios y los ficticios para la lista de subtotales
 */
QModelIndex MCompraProductos::index( int row, int column, const QModelIndex & parent ) const
{
 if( column == 5 )
 {
  return createIndex( row, 5 , 0 );
 }
 else
 {
  return QSqlRelationalTableModel::index( row, column, parent );
 }
}


/*!
    \fn MCompraProductos::columnCount( const QModelIndex & parent = QModelIndex() ) const
	Devuleve la cantidad de columnas del modelo mas una si el modelo esta en modo calcular totales
 */
int MCompraProductos::columnCount( const QModelIndex & parent ) const
{
 if( calculaTotales )
 {
  return QSqlRelationalTableModel::columnCount( parent ) + 1;
 }
 else
 {
  return QSqlRelationalTableModel::columnCount( parent );
 }
}


/*!
    \fn MCompraProductos::setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole )
 */
bool MCompraProductos::setData( const QModelIndex & index, const QVariant & value, int role )
{
  if( !index.isValid() )
  {
   qDebug( QString( "Indice invalido Dueños: col=%1, row=%2, role=%3").arg( index.column() ).arg( index.row() ).arg( role ).toLocal8Bit() );
   return false;
  }
  switch( role )
  {
	case Qt::EditRole:
	{
		switch( index.column() )
		{
			// Subtotal
			case 5:
			{
				return true;
			}
			// Precio
			case 3:
			{
				// Recalculo el valor
				QVariant valor = data( this->index( index.row(), 4 ), Qt::EditRole );
				if( valor.isValid() || valor.toDouble() > 0 )
				{
				  subtotales->insert( index.row(), ( this->data( this->index( index.row(), 4 ), Qt::EditRole ).toDouble() * value.toDouble() ) );
				  recalcularTotal();
				  emit dataChanged( this->index( QSqlRelationalTableModel::rowCount() + 1, 5 ), this->index( QSqlRelationalTableModel::rowCount() + 1, 5 ) ); // total
				}
				return QSqlRelationalTableModel::setData( index, value, role );
			}
			// Cantidad
			case 4:
			{
				// Recalculo el valor
				QVariant valor = data( this->index( index.row(), 3 ), Qt::EditRole );
				if( valor.isValid() || valor.toDouble() > 0 )
				{
				  subtotales->insert( index.row(), ( this->data( this->index( index.row(), 3 ), Qt::EditRole ).toDouble() * value.toDouble() ) );
				  recalcularTotal();
				  emit dataChanged( this->index( QSqlRelationalTableModel::rowCount() + 1, 5 ), this->index( QSqlRelationalTableModel::rowCount() + 1, 5 ) ); // total
				}
				return QSqlRelationalTableModel::setData( index, value, role );
			}
			default:
			{
				return QSqlRelationalTableModel::setData( index, value, role );
			}
		}
		break;
	}
        case Qt::DisplayRole:
	{
		return QSqlRelationalTableModel::setData( index, value, role );
		break;
	}
	default:
	{
		qDebug( QString( "Rol de SetData desconocido: %1" ).arg( role ).toLocal8Bit() );
		return false;
	}
  }
}


/*!
    \fn MCompraProductos::flags ( const QModelIndex & index ) const
     Reimplementacion necesaria para determinar que los items de la columna 6 no son editables
 */
Qt::ItemFlags MCompraProductos::flags ( const QModelIndex &index ) const
{
 if( index.row() == QSqlRelationalTableModel::rowCount() + 1 ) {
  return !Qt::ItemIsEnabled && !Qt::ItemIsSelectable;
 } else if( index.column() >= 5 && calculaTotales ) {
  return Qt::ItemIsEnabled && !Qt::ItemIsEditable && Qt::ItemIsSelectable;
 } else {
  return QSqlRelationalTableModel::flags( index );
 }
}


/*!
    \fn MCompraProductos::isDirty( const QModelIndex & index ) const
	Limita el intento de actualizacion cuando la columna es mayor a 6 y estamos calculando los totales
 */
bool MCompraProductos::isDirty( const QModelIndex & index ) const
{
 if( calculaTotales && index.column() == 6 )
 {
  return false;
 }
 else
 {
  return QSqlRelationalTableModel::isDirty( index );
 }
}


/*!
    \fn MCompraProductos::recalcularTotal()
	Recalcula el total de compras mediante los subtotales
 */
void MCompraProductos::recalcularTotal()
{
 Total = 0;
 for( QHash<int, double>::const_iterator i = subtotales->constBegin(); i != subtotales->constEnd(); ++i )
 {
  Total += i.value();
 }
}


int MCompraProductos::get_ultima_row() const
{
	return ultima_row;
}


/*!
    \fn MCompraProductos::primeInsert ( int row, QSqlRecord & record )
	Funcion que guarda la posicion de la ultima fila
 */
void MCompraProductos::primeInsert ( int row, QSqlRecord & record )
{
 ultima_row = row;
 QSqlRelationalTableModel::primeInsert( row, record );
}

#include <QSqlRecord>
/*!
    \fn MCompraProductos::insertarRegistro()
	Funcion creada por comodidad para agregar un registro vacio
 */
void MCompraProductos::insertarRegistro()
{
 this->insertRecord( -1, this->record() );
}


/*!
    \fn MCompraProductos::rowCount( QModelIndex &parent )
	Devuleve la cantidad de columnas mas una mas que indica la cantidad y el total hasta ahora
 */
int MCompraProductos::rowCount( const QModelIndex &parent ) const
{
  int conteo = QSqlRelationalTableModel::rowCount() + 1;
  return conteo;
}



/*!
    \fn MCompraProductos::eliminarFila( int fila )
 */
void MCompraProductos::eliminarFila( int fila )
{
 subtotales->remove( fila );
}
