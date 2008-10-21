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
#include "mventaproducto.h"

#include <QColor>
#include <QSize>

MVentaProducto::MVentaProducto(QObject *parent , bool calcula )
 : QSqlRelationalTableModel(parent)
{
 setTable( "ventas_productos" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Numero de Venta" );
 setRelation( 1, QSqlRelation( "ventas", "id", "id" ) );
 setHeaderData( 2, Qt::Horizontal, "Producto" );
 setRelation( 2, QSqlRelation( "producto", "id", "nombre" ) );
 setHeaderData( 3, Qt::Horizontal, "Precio" );
 setHeaderData( 4, Qt::Horizontal, "Cantidad" );
 if( calcula )
 {
  calcularTotales();
  setHeaderData( 5, Qt::Horizontal, "SubTotal" );
  subtotales = new QHash<int, double>();
  setEditStrategy( QSqlTableModel::OnManualSubmit );
 }
}


MVentaProducto::~MVentaProducto()
{
}




/*!
    \fn MVentaProducto::data(const QModelIndex& idx, int role) const
 */
QVariant MVentaProducto::data(const QModelIndex& idx, int role) const
{
  if( !idx.isValid() )
  {
   qDebug( QString( "Indice invalido Dueños: col=%1, row=%2, role=%3").arg( idx.column() ).arg( idx.row() ).arg( role ).toLocal8Bit() );
   return( QVariant() );
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
				return QSqlRelationalTableModel::data(idx, role).toString().prepend("$");
				break;
			}
			case 5:
			{
				if( calculaTotales )
				{
					// Busco si existe
					if( subtotales->find( idx.row() ) != subtotales->end() )
					{
						return QVariant::fromValue( subtotales->value( idx.row() ) ).toString().prepend( "$" );
					}
					else
					{
						// Calculo el valor
						double sub = data( index( idx.row(), 3 ), Qt::EditRole ).toDouble() * data( index( idx.row(), 4 ), Qt::EditRole ).toDouble();
 						subtotales->insert( idx.row(), sub );
						return QVariant::fromValue( sub ).toString().prepend( "$" );
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
			case 3:
			{
				return QSqlRelationalTableModel::data( idx, role ).toDouble();
				break;
			}
			case 4:
			case 5:
			{
				return QSqlRelationalTableModel::data( idx, role ).toInt();
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
	           tam.setWidth( 110 );
	           return tam;
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

	case Qt::TextAlignmentRole:
	{
		switch ( idx.column() )
		{
			case 0:
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
    \fn MVentaProducto::calcularTotales()
 */
void MVentaProducto::calcularTotales()
{
  calculaTotales = true;
}


/*!
    \fn MVentaProducto::total()
 */
double MVentaProducto::total()
{
 return Total;
}


/*!
    \fn MVentaProducto::index( int row, int column, const QModelIndex & parent = QModelIndex() ) const
 */
QModelIndex MVentaProducto::index( int row, int column, const QModelIndex & parent ) const
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
    \fn MVentaProducto::columnCount( const QModelIndex & parent = QModelIndex() ) const
 */
int MVentaProducto::columnCount( const QModelIndex & parent ) const
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
    \fn MVentaProducto::setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole )
 */
bool MVentaProducto::setData( const QModelIndex & index, const QVariant & value, int role )
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
			case 3:
			{
				// Recalculo el valor
				QVariant valor = data( this->index( index.row(), 4 ), Qt::EditRole );
				if( valor.isValid() || valor.toDouble() > 0 )
				{
				  subtotales->insert( index.row(), ( this->data( this->index( index.row(), 4 ), Qt::EditRole ).toDouble() * value.toDouble() ) );
				  recalcularTotal();
				}
				return QSqlRelationalTableModel::setData( index, value, role );
			}
			case 4:
			{
				// Recalculo el valor
				QVariant valor = data( this->index( index.row(), 3 ), Qt::EditRole );
				if( valor.isValid() || valor.toDouble() > 0 )
				{
				  subtotales->insert( index.row(), ( this->data( this->index( index.row(), 3 ), Qt::EditRole ).toDouble() * value.toDouble() ) );
				  recalcularTotal();
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
    \fn MVentaProducto::flags ( const QModelIndex & index ) const
     Reimplementacion necesaria para determinar que los items de la columna 6 no son editables
 */
Qt::ItemFlags MVentaProducto::flags ( const QModelIndex & index ) const
{
 if ( index.column() == 6 && calculaTotales )
 {
	return Qt::ItemIsSelectable && Qt::ItemIsEnabled && !Qt::ItemIsEditable;
 }
 else
 {
  return QSqlRelationalTableModel::flags( index );
 }
}


/*!
    \fn MVentaProducto::isDirty( const QModelIndex & index ) const
 */
bool MVentaProducto::isDirty( const QModelIndex & index ) const
{
 if( calculaTotales && index.column() == 5 )
 {
  return false;
 }
 else
 {
  return QSqlRelationalTableModel::isDirty( index );
 }
}


/*!
    \fn MVentaProducto::recalcularTotal()
	Recalcula el total de compras mediante los subtotales
 */
void MVentaProducto::recalcularTotal()
{
 Total = 0;
 for( QHash<int, double>::const_iterator i = subtotales->constBegin(); i != subtotales->constEnd(); ++i )
 {
  Total += i.value();
 }
}



/*!
    \fn MVentaProducto::primeInsert ( int row, QSqlRecord & record )
 */
void MVentaProducto::primeInsert ( int row, QSqlRecord & record )
{
  ultima_row = row;
  QSqlRelationalTableModel::primeInsert( row, record );
}


int MVentaProducto::get_ultima_row() const
{
	return ultima_row;
}
