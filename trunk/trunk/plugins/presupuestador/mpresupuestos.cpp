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
#include "mpresupuestos.h"
#include <QColor>
#include <QDate>

MPresupuestos::MPresupuestos(QObject *parent)
 : QSqlTableModel(parent)
{
 setTable( "presupuestos" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Destinatario" );
 setHeaderData( 2, Qt::Horizontal, "Fecha" );
 setHeaderData( 3, Qt::Horizontal, "Costo" );
 select();
}


MPresupuestos::~MPresupuestos()
{
}


QVariant MPresupuestos::data(const QModelIndex& idx, int role) const
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
			case 3:
			{
				return QSqlTableModel::data(idx, role).toString().prepend("$ ");
				break;
			}
			case 2:
			{
			       return QSqlTableModel::data(idx, role).toDate().toString( Qt::SystemLocaleDate );
			       break;
			}
			default:
			{
				return QSqlTableModel::data(idx, role);
				break;
			}
		}
		break;
	}
	case Qt::TextColorRole:
	{
		switch ( idx.column() )
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
		switch( idx.column() )
 		{
			case 3:
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
	case Qt::TextAlignmentRole:
	{
		switch ( idx.column() )
		{
			case 3:
			{
				return int( Qt::AlignRight | Qt::AlignVCenter );
				break;
			}
			case 2:
			{
			   return int( Qt::AlignCenter | Qt::AlignVCenter );
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
	default:
	{
		return QSqlTableModel::data( idx, role);
		break;
	}
 }
}

Qt::ItemFlags MPresupuestos::flags(const QModelIndex& index) const
{
    return QSqlTableModel::flags(index);
}

