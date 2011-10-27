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
#include "mcompra.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QDate>

MCompra::MCompra(QObject *parent, bool relaciones )
 : QSqlRelationalTableModel(parent)
{
    inicializar();
    if( relaciones )
        relacionar();
}

void MCompra::inicializar()
{
    setTable( "compras" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Proveedor" );
    setHeaderData( 2, Qt::Horizontal, "Fecha" );
    setHeaderData( 3, Qt::Horizontal, "Costo" );
}

void MCompra::relacionar()
{
    setRelation( 1, QSqlRelation( "proveedor", "id", "nombre" ) );
}

/*!
    \fn MCompra::agregarCompra( QVariant fecha, QVariant proveedor )
	Función que agrega un registro de compra directamente
	@param fecha QDate con la fecha de la compra
	@param proveedor Id del proveedor
        @param total Total de la compra
	@return Verdadero o falso si fue exitoso o no
 */
bool MCompra::agregarCompra( QVariant fecha, QVariant proveedor, double total )
{
 QSqlRecord regCompra = record();
 regCompra.remove( 0 );
 regCompra.setValue( "fecha"       , fecha );
 regCompra.setValue( "id_proveedor", proveedor );
 regCompra.setValue( "total", total );
 if( !insertRecord( -1, regCompra ) )
 {
  qDebug( "Error de insercion de registro de compra" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( lastError().type() ).arg( lastError().number() ).arg( lastError().text() ).toLocal8Bit() );
  return false;
 }
 else
 { return true; }
}


/*!
    \fn MCompra::data(const QModelIndex &index, int role ) const
 */
QVariant MCompra::data(const QModelIndex &index, int role ) const
{
 switch( role )
 {
	case Qt::TextAlignmentRole:
	{
		if( index.column() == 2 )
		{
			return int( Qt::AlignHCenter | Qt::AlignVCenter );
		}
		else if( index.column() == 3 )
		{
			return int( Qt::AlignRight | Qt::AlignVCenter );
		}
		else
		{
			return QSqlRelationalTableModel::data( index, role );
		}
		break;
	}
	case Qt::DisplayRole:
	{
		switch( index.column() )
		{
			case 3:
			{
				return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( index, role ).toDouble(), 8, 'f', 2 );
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data( index, role );
				break;
			}
		}
		break;
	}
	case Qt::EditRole:
	{
		switch( index.column() )
		{
			case 3:
			{
				return QSqlRelationalTableModel::data( index, role ).toDouble();
				break;
			}
			case 2:
			{
				return QSqlRelationalTableModel::data( index, role ).toDate();
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data( index, role );
			}
		}
	}
	case Qt::ToolTipRole:
	case Qt::StatusTipRole:
	{
		return QVariant( "Haga doble click o seleccione y F2 para editar" );
		break;
	}
	default:
	{
		return QSqlRelationalTableModel::data( index, role );
		break;
	}
 }
}

#include <QSqlQuery>
/*!
    \fn MCompra::ultimoId()
 */
int MCompra::ultimoId()
{ return this->query().lastInsertId().toInt(); }
