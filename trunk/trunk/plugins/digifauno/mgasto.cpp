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
#include "mgasto.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QDate>
#include <QColor>

MGasto::MGasto(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "gastos" );
 setHeaderData( 0, Qt::Horizontal, "ID#" );
 setHeaderData( 1, Qt::Horizontal, "Categoria" );
 setRelation(   1, QSqlRelation( "categoria", "id", "nombre" ) );
 setHeaderData( 2, Qt::Horizontal, "Descripcion" );
 setHeaderData( 3, Qt::Horizontal, "Costo" );
 setHeaderData( 4, Qt::Horizontal, "Fecha" );
}


MGasto::~MGasto()
{
}

QVariant MGasto::data(const QModelIndex& item, int role) const
{
 if( !item.isValid() )
  {
   qDebug( QString( "Indice invalido Gasto: col=%1, row=%2, role=%3").arg( item.column() ).arg( item.row() ).arg( role ).toLocal8Bit() );
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
				return QSqlRelationalTableModel::data(item, role).toString().prepend("$");
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
	case Qt::TextAlignmentRole:
	{
		switch ( item.column() )
		{
			case 3:
			case 4:
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
    \fn MGasto::agregarGasto( QString descripcion, double costo, QDate Fecha, int categoria )
 */
bool MGasto::agregarGasto( QString descripcion, double costo, QDate Fecha, int categoria )
{
 QSqlRecord registro = this->record();
 registro.setValue( "descripcion", descripcion );
 registro.setValue( "costo", costo );
 registro.setValue( "fecha", Fecha );
 registro.setValue( 1, categoria );
 registro.remove( 0 );
 if( insertRecord( -1, registro ) == false )
 {
  qDebug( "Error al insertar registro de mascota" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( lastError().type() ).arg( lastError().number() ).arg( lastError().text() ).toLocal8Bit() );
  return false;
 }
 else
 {
//   qDebug( "Gasto agregado correctamente" );
  return true;
 }
}
