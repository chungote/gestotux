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
#include "mpagos.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>

MPagos::MPagos(QObject *parent, bool relaciones )
 : QSqlRelationalTableModel(parent)
{
 setTable( "recibos" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Cliente" );
 setHeaderData( 2, Qt::Horizontal, "Texto" );
 setHeaderData( 3, Qt::Horizontal, "Cantidad" );
 setHeaderData( 4, Qt::Horizontal, "Fecha Pago" );
 setHeaderData( 5, Qt::Horizontal, "Cancelado" );
 setHeaderData( 6, Qt::Horizontal, "Template" );
 if( relaciones )
 {
  setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
 }
}


MPagos::~MPagos()
{
}


bool MPagos::setData(const QModelIndex& item, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(item, value, role);
}

QVariant MPagos::data(const QModelIndex& item, int role) const
{
 switch( role )
 {
  case Qt::DisplayRole:
  {
   switch( item.column() )
   {
     case 0:
     { return QString( "#%L1" ).arg( QSqlRelationalTableModel::data( item, role ).toInt() ); break;}
     case 1:
     {
	return QSqlRelationalTableModel::data( item, role ).toString();
      break;
     }
     case 2:
     { return QSqlRelationalTableModel::data( item, role ).toString(); break; }
     case 3:
     { return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( item, role ).toDouble() ); break; }
     case 4:
     { return QSqlRelationalTableModel::data( item, role ).toDate(); break; }
     case 5:
     { return QSqlRelationalTableModel::data( item, role ).toString(); break; }
     default:
     { return QSqlRelationalTableModel::data( item, role ); break; }
   }
   break;
  }
  case Qt::TextAlignmentRole:
  {
   switch( item.column() )
   {
    case 3:
    case 4:
    case 5:
    { return int( Qt::AlignCenter | Qt::AlignVCenter ); break; }
    default:
    { return QSqlRelationalTableModel::data( item, role ); break; }
   }
   break;
  }
  default:
  {
   return QSqlRelationalTableModel::data( item, role );
   break;
  }
 }
    return QSqlRelationalTableModel::data(item, role);
}
