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
#include "mproductos.h"
#include "preferencias.h"
#include <QColor>
#include <QSqlError>
#include <QSqlQuery>

MProductos::MProductos(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "producto" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Categoria" );
   setRelation( 1, QSqlRelation( "categoria", "id", "nombre" ) );
 setHeaderData( 2, Qt::Horizontal, "Nombre" );
 setHeaderData( 3, Qt::Horizontal, "Precio de Venta" );
 setHeaderData( 4, Qt::Horizontal, "Descripcion" );
 setHeaderData( 5, Qt::Horizontal, "Marca" );
}


MProductos::~MProductos()
{
}


QVariant MProductos::data(const QModelIndex& item, int role) const
{
if( !item.isValid() )
 {
   qDebug( QString( "Indice invalido Dueños: col=%1, row=%2, role=%3").arg( item.column() ).arg( item.row() ).arg( role ).toLocal8Bit() );
   return( QVariant() );
 }
 switch( role )
 {
	case Qt::DisplayRole:
	{
		switch( item.column() )
		{
			case 3:
			{
				return QSqlRelationalTableModel::data(item, role).toString().prepend( "$" );
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
	case Qt::TextColorRole:
	{
		switch ( item.column() )
		{
			case 3:
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
		switch( item.column() )
		{
			case 3:
			{
				return QSqlRelationalTableModel::data( item, role ).toDouble();
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
	case Qt::DecorationRole:
	case Qt::FontRole:
	case Qt::SizeHintRole:
	{
		return QVariant();
		break;
	}
	case Qt::TextAlignmentRole:
	{
		return int( Qt::AlignLeft | Qt::AlignVCenter );
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
		return QSqlRelationalTableModel::data( item, role);
		break;
	}
 }
}



/*!
    \fn MProductos::setData( const QModelIndex & index, const QVariant & value, int role )
 */
bool MProductos::setData( const QModelIndex & index, const QVariant & value, int role )
{
 return QSqlRelationalTableModel::setData( index, value, role );
}
