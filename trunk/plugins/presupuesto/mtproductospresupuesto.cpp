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
 setTable( "presupuestos_productos" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "#Presupuesto" );
 setHeaderData( 2, Qt::Horizontal, "Producto" );
   setRelation( 2, QSqlRelation( "producto", "id", "nombre" ) );
 setHeaderData( 3, Qt::Horizontal, "Cantidad" );
 setHeaderData( 4, Qt::Horizontal, "Precio Unitario" );
 setEditStrategy( QSqlTableModel::OnManualSubmit );
}


MTProductosPresupuesto::~MTProductosPresupuesto()
{
}

/*!
    \fn MTProductosPresupuesto::data ( const QModelIndex & item, int role ) const
 */
QVariant MTProductosPresupuesto::data( const QModelIndex & item, int role ) const
{
 switch( item.column() )
 {
   // id del producto
   case 2:
   {
	switch( role )
	{
		case Qt::UserRole:
		{
			// retorno el id, si no hay uno puesto, retorno -1
			if( QSqlRelationalTableModel::data( item, Qt::EditRole ).toInt() >= 0 )
			{
				return QSqlRelationalTableModel::data( item, Qt::EditRole ).toInt();
			}
			else
			{
				return -1;
			}
			break;
		}
		default:
		{
			return QSqlRelationalTableModel::data( item, role );
			break;
		}
	}
	break;
   }
   // Precio Unitario
   case 4:
   {
	// Busco el id del producto
	int id = data( index( item.column(), 2 ), Qt::UserRole ).toInt();
	if( id != -1 )
	{
		QSqlQuery cola( QString("SELECT precio FROM producto WHERE id = '%1'").arg( id ) );
		if( cola.next() )
		{
			return QString( "$ %L1" ).arg( cola.record().value(0).toString() );
		}
		else
		{
			qWarning( "Error al buscar el precio del producto" );
			return QVariant();
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
  case 4:
  {
	return int( !Qt::ItemIsEditable );
 	break;
  }
  default:
  {
    return QSqlRelationalTableModel::flags( index );
    break;
  }
 }
}


/*!
    \fn MTProductosPresupuesto::columnCount( QModelIndex &parent )
 */
int MTProductosPresupuesto::columnCount( const QModelIndex &parent ) const
{
  int conteo = QSqlRelationalTableModel::columnCount() +1;
  return conteo;
}


/*!
    \fn MTProductosPresupuesto::guardar( const int id_presupuesto )
 */
bool MTProductosPresupuesto::guardar( const int id_presupuesto ) const
{
 return false;
}
