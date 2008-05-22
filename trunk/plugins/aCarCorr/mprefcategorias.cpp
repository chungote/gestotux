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
#include "mprefcategorias.h"

MPrefCategorias::MPrefCategorias(QObject *parent)
 : QSqlTableModel(parent)
{
 setTable( "car_categorias" );
 setHeaderData( 0, Qt::Horizontal, "#id_db" );
 setHeaderData( 1, Qt::Horizontal, "Categoria" );
 setHeaderData( 2, Qt::Horizontal, "Especial" );
 setEditStrategy( QSqlTableModel::OnManualSubmit );
}


MPrefCategorias::~MPrefCategorias()
{
}


QVariant MPrefCategorias::data(const QModelIndex& index, int role) const
{
 if( !index.isValid() )
 { return QVariant(); }
 switch( index.column() )
 {
	case 2:
	{
		switch( role )
		{
			case Qt::DisplayRole:
			{
				if( QSqlTableModel::data( index, role ).toBool() )
				{
					return "Si";
				}
				else
				{
					return "No";
				}
				break;
			}
			case Qt::EditRole:
			{
				return QSqlTableModel::data( index, role ).toBool();
				break;
			}
			default:
			{
				return QSqlTableModel::data( index, role );
				break;
			}
		}
		break;
	}
	default:
	{
		return QSqlTableModel::data( index, role );
		break;
	}
 }
 return QVariant();
}

Qt::ItemFlags MPrefCategorias::flags( const QModelIndex & index ) const
{
 if( index.column() != 2 )
 {
	return QSqlTableModel::flags( index ) & !Qt::ItemIsEditable;
 }
 else
 {
	return QSqlTableModel::flags( index );
 }
}
