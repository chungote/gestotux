/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
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
#include "mtproductospresupuesto.h"

#include <QSqlQuery>
#include <QSqlRecord>

MTProductosPresupuesto::MTProductosPresupuesto( QObject * parent )
 : QSqlRelationalTableModel( parent)
{
 QSqlQuery cola( "CREATE TEMPORARY TABLE prod_presupuesto ( id INTEGER AUTOINCREMENT, id_prod INTEGER, cantidad NUMBER )" );
 setTable( "prod_presupuesto" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Id Producto" );
   setRelation( 1, QSqlRelation( "productos", "id", "nombre" ) );
 setHeaderData( 2, Qt::Horizontal, "Precio Unitario" );
 setHeaderData( 3, Qt::Horizontal, "Cantidad" );
 setHeaderData( 4, Qt::Horizontal, "Sub-Total" );
 
}


MTProductosPresupuesto::~MTProductosPresupuesto()
{
}

/*!
    \fn MTProductosPresupuesto::setData ( const QModelIndex & index, const QVariant & value, int role )
 */
bool MTProductosPresupuesto::setData ( const QModelIndex & index, const QVariant & value, int role )
{
 switch( index.column() )
 {
  case 4:
  case 2:
  {
	return true;
	break;
  }
  case 3:
  {
	return QSqlRelationalTableModel::setData( this->index( index.row(), 2 ), value, role );
	break;
  }
  default:
  {
   return QSqlRelationalTableModel::setData( index, value, role );
   break;
  }
 }
}

/*!
    \fn MTProductosPresupuesto::data ( const QModelIndex & item, int role ) const
 */
QVariant MTProductosPresupuesto::data ( const QModelIndex & item, int role ) const
{
  switch( item.column() )
 {
  case 2:
  {
	switch( role )
	{
		case Qt::DisplayRole:
		{
			QSqlQuery cola( QString( "SELECT precio FROM productos WHERE id_producto = '%1'").arg( QSqlRelationalTableModel::data( index( item.row(), 2 ), Qt::UserRole ).toInt() ) );
			if( cola.next() )
			{
				return QString( "$ %L1" ).arg( cola.record().value(0).toDouble() );
			}
			else
			{
				qWarning( "Error al buscar le precio" );
				return QVariant();
			}
			break;
		}
		case Qt::UserRole:
		{
			QSqlQuery cola( QString( "SELECT precio FROM productos WHERE id_producto = '%1'").arg( QSqlRelationalTableModel::data( index( item.row(), 2 ), Qt::UserRole ).toInt() ) );
			if( cola.next() )
			{
				return cola.record().value(0).toDouble();
			}
			else
			{
				qWarning( "Error al buscar le precio" );
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
	break;
  }
  case 4:
  {
	switch( role )
	{
		case Qt::DisplayRole:
		{
			// calculo el subtotal
			double cant = data( index( item.row(), 3 ), role ).toDouble();
			double precio = data( index( item.row(), 3 ), Qt::UserRole ).toDouble();
			return QString( "$ %L1" ).arg( precio * cant );
			break;
		}
		case Qt::TextAlignmentRole:
		{
			return int( Qt::AlignCenter || Qt::AlignVCenter );
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
  case 3:
  {
	// Necesario para usar el redireccionamiento
	return QSqlRelationalTableModel::data( index( item.row(), 2 ), role );
	break;
  }
  default:
  {
   return QSqlRelationalTableModel::data( item, role );
   break;
  }
 }
  
}


/*!
    \fn MTProductosPresupuesto::QAbstractItemModel::flags ( const QModelIndex & index ) const
 */
Qt::ItemFlags MTProductosPresupuesto::flags ( const QModelIndex & index ) const
{
  switch( index.column() )
  {
   case 2:
   case 4:
   {
	return Qt::ItemIsSelectable && !Qt::ItemIsEditable && Qt::ItemIsEnabled;
	break;
   }
   default:
   {
    return QSqlRelationalTableModel::flags( index );
    break;
   }
  }
}
