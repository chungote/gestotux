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

/*
CREATE TABLE IF NOT EXISTS `recibos` (
  `id_recibo` int(10) NOT NULL AUTO_INCREMENT,
  `id_cliente` bigint REFERENCES clientes(id),
  `fecha_pago` datetime NOT NULL,
  `texto` tinyblob DEFAULT NULL,
  `precio` double(15,4) DEFAULT NULL,
  `cancelado` tinyint NOT NULL DEFAULT 0,
  `pagado` tinyint NOT NULL DEFAULT 1,
  PRIMARY KEY (`id_recibo`)
) ENGINE=InnoDB;
*/

MPagos::MPagos(QObject *parent, bool relaciones )
 : QSqlRelationalTableModel(parent)
{
 setTable( "recibos" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Cliente" );
 setHeaderData( 2, Qt::Horizontal, "Fecha Pago" );
 setHeaderData( 3, Qt::Horizontal, "Texto" );
 setHeaderData( 4, Qt::Horizontal, "Cantidad" );
 setHeaderData( 5, Qt::Horizontal, "Cancelado" );
 setHeaderData( 6, Qt::Horizontal, "Pagado" ); // Campo utilizado en hicomp
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
     case 0: // ID
     { return QString( "#%L1" ).arg( QSqlRelationalTableModel::data( item, role ).toInt() ); break;}
     case 1: // Cliente
     { return QSqlRelationalTableModel::data( item, role ).toString(); break; }
     case 2: // fecha de pago
     { return QSqlRelationalTableModel::data( item, role ).toDate(); break; }
     case 3: // Texto
     { return QSqlRelationalTableModel::data( item, role ).toString(); break; }
     case 4: // Cantidad pagada
     { return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( item, role ).toDouble() ); break; }
     case 5: // Cancelado ( anulado )
     { return QSqlRelationalTableModel::data( item, role ).toBool(); break; }
     case 6: // Pagado ( solo hicomp - por default en true )
     { return QSqlRelationalTableModel::data( item, role ).toBool(); break; }
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
