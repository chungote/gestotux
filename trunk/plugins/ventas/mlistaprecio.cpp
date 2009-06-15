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
#include "mlistaprecio.h"

MListaPrecio::MListaPrecio(QObject *parent)
 : QSqlTableModel(parent)
{
 setTable( "lista_precio" );
 setHeaderData( 0, Qt::Horizontal, "Id" );
 setHeaderData( 1, Qt::Horizontal, "Nombre" );
 setHeaderData( 2, Qt::Horizontal, "Descripcion" );
 setHeaderData( 3, Qt::Horizontal, "Recargo" );
 setHeaderData( 4, Qt::Horizontal, "Habilitado" );
}


MListaPrecio::~MListaPrecio()
{
}


QVariant MListaPrecio::data(const QModelIndex& idx, int role) const
{

 switch( idx.column() ) {
	// 0 -  Id
	// 1 Nombre
	// 2 Descripcion
	// 3 recargo
	case 3:
	{
		switch( role )
		{
			case Qt::DisplayRole:
			{
				return QString::number( QSqlTableModel::data( idx, role ).toDouble() ).append( " %" );
				break;
			}
			case Qt::TextAlignmentRole:
			{
				return int( Qt::AlignVCenter | Qt::AlignCenter );
				break;
			}
			case Qt::EditRole:
			{
				return QSqlTableModel::data( idx, role ).toDouble();
				break;
			}
			default:
			{
				return QSqlTableModel::data( idx, role );
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
				if( QSqlTableModel::data( idx, role ).toBool() )
				{ return "Si"; }
				else
				{ return "No"; }
				break;
			}
			case Qt::TextAlignmentRole:
			{
				return int( Qt::AlignVCenter | Qt::AlignCenter );
				break;
			}
			case Qt::EditRole:
			{
				return QSqlTableModel::data( idx, role ).toBool();
				break;
			}
			default:
			{
				return QSqlTableModel::data( idx, role );
			}
		}
		break;
	}
 	default: {
		return QSqlTableModel::data(idx, role);
		break;
	}
 }
}

