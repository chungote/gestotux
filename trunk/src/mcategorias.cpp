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
#include "mcategorias.h"

#include <QSqlIndex>
#include <QSqlDatabase>

MCategorias::MCategorias(QObject *parent)
 : QSqlTableModel(parent)
{
 setTable( "categoria" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Nombre" );
 setHeaderData( 2, Qt::Horizontal, "Descripcion" );
 setHeaderData( 3, Qt::Horizontal, "Tipo" ); // 1 = salida, 0 = entradas
 setSort( 1, Qt::AscendingOrder );
 setEditStrategy( QSqlTableModel::OnRowChange );
 select();
}


MCategorias::~MCategorias()
{
}




/*!
    \fn MCategorias::data( const QModelIndex& item, int role ) const
 */
QVariant MCategorias::data( const QModelIndex& item, int role ) const
{
if( !item.isValid() )
 {
  return QVariant();
 }
 else
 {
  switch(role)
  {
	case Qt::DisplayRole:
	{
		switch( item.column() )
		{
			case 3:
			{
				switch( QSqlTableModel::data( item, role ).toInt() )
				{
					case 1:
					{
						return "Compras";
						break;
					}
					case 2:
					{
						return "Gastos";
						break;
					}
					default:
					{
						return "Ventas";
						break;
					}
				}
				break;
			}
			default:
			{
				return QSqlTableModel::data( item, role );
				break;
			}
		}
		break;
	}
	default:
	{
		return QSqlTableModel::data( item, role );
		break;
	}
  }
 }
}
