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
#include "mproductos.h"
#include "preferencias.h"
#include <QColor>
#include <QBrush>

MProductos::MProductos(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "producto" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Categoria" );
 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 {
  setRelation( 1, QSqlRelation( "categoria", "id", "nombre" ) );
 }
 setHeaderData( 2, Qt::Horizontal, "Nombre" );
 setHeaderData( 3, Qt::Horizontal, "Precio de Costo" );
 setHeaderData( 4, Qt::Horizontal, "Descripcion" );
 setHeaderData( 5, Qt::Horizontal, "Marca" );
 setHeaderData( 6, Qt::Horizontal, "Habilitado" );
 setHeaderData( 7, Qt::Horizontal, "Stock" );
 setSort( 0, Qt::AscendingOrder );
}


MProductos::~MProductos()
{
}

QVariant MProductos::data(const QModelIndex& item, int role) const
{
 if( !item.isValid() )
 {
   qDebug( QString( "Indice invalido Productos: col=%1, row=%2, role=%3").arg( item.column() ).arg( item.row() ).arg( role ).toLocal8Bit() );
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
			case 6:
			{
				if( QSqlRelationalTableModel::data( item, role ).toBool() )
				{ return "Si"; }
				else
				{ return "No"; }
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
	case Qt::TextAlignmentRole:
	{
		switch( item.column() )
		{
			case 3:
			case 6:
			case 7:
			{
				return int( Qt::AlignHCenter | Qt::AlignVCenter );
				break;
			}
			default:
			{
				return int( Qt::AlignLeft | Qt::AlignVCenter );
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
	{
		return QSqlRelationalTableModel::data( item, role );
		break;
	}
 }
}



/*!
    \fn MProductos::stock( const int id_producto )
	Devuelve la cantidad de stock que existe de un producto si el control de stock esta habilitado
 */
double MProductos::stock( const int id_producto )
{
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/stock" ).toBool() )
 { return 0; }
}


/*!
    \fn MProductos::modificarStock( const int id_producto, const double cantidad )
 */
bool MProductos::modificarStock( const int id_producto, const double cantidad )
{
    /// @todo implement me
}
