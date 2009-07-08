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
#include "mcuentacorriente.h"

#include <QColor>

MCuentaCorriente::MCuentaCorriente(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "ctacte" ),
 setHeaderData( 0, Qt::Horizontal, "Numero de cuenta" );
 setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
 setHeaderData( 1, Qt::Horizontal, "Cliente" );
 setHeaderData( 2, Qt::Horizontal, "Fecha Alta" );
 setHeaderData( 3, Qt::Horizontal, "Fecha Baja" );
 setHeaderData( 4, Qt::Horizontal, "Saldo" );
 setHeaderData( 5, Qt::Horizontal, "Limite" );
}


MCuentaCorriente::~MCuentaCorriente()
{
}


QVariant MCuentaCorriente::data(const QModelIndex& item, int role) const
{
 switch( role )
 {
	case Qt::DisplayRole:
	{
		switch( item.column() )
		{
			case 0:
			{
				return QSqlRelationalTableModel::data(item, role).toString().prepend( "#" );
				break;
			}
			case 4:
			case 5:
			{
				return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data(item,role).toDouble() );
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data(item, role);
				break;
			}
		}
		break;
	}
	case Qt::TextAlignmentRole:
	{
		switch( item.column() )
		{
			case 0:
			case 2:
			case 3:
			case 4:
			case 5:
			{
				return Qt::AlignCenter;
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data(item, role);
				break;
			}
		}
		break;
	}
	case Qt::TextColorRole:
	{
		switch( item.column() )
		{
			case 0:
			{
				return Qt::blue;
				break;
			}
			case 4:
			{
				if( this->data( this->index( item.row(), 4 ), Qt::EditRole ).toDouble() >= this->data( this->index( item.row(), 5 ), Qt::EditRole ).toDouble() )
				{ return Qt::red; }
				else
				{ return Qt::black; }
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data(item, role);
				break;
			}
		}
		break;
	}
	default:
	{
		return QSqlRelationalTableModel::data(item, role);
	}
 }
}

