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

#include "MClientesServicios.h"

MClientesServicios::MClientesServicios(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
   this->setTable( "servicios_clientes" );
   this->setHeaderData( 0, Qt::Horizontal, "Servicio" );
   this->setHeaderData( 1, Qt::Horizontal, "Cliente");
   this->setHeaderData( 2, Qt::Horizontal, "Fecha Alta" );
   this->setHeaderData( 3, Qt::Horizontal, "Fecha Baja" );
   // Relaciones
   this->setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
   this->setRelation( 0, QSqlRelation( "servicios", "id_servicio", "nombre" ) );
}

void MClientesServicios::filtrarPorCliente( const int id_cliente )
{
    this->setFilter( QString( "servicios_clientes.id_cliente = %1 ").arg( id_cliente ) );
}

void MClientesServicios::filtrarPorServicio( const int id_servicio )
{
    this->setFilter( QString( "servicios_clientes.id_servicio = %1 ").arg( id_servicio ) );
}

QVariant MClientesServicios::data(const QModelIndex &item, int role) const
{
 switch( item.column() ) {
    case 2:
    case 3:
    {
     switch( role ) {
        case Qt::TextAlignmentRole:
        {  return int( Qt::AlignCenter | Qt::AlignVCenter ); break; }
        default:
        { return QSqlRelationalTableModel::data( item, role ); break; }
     }
     break;
    }
    default:
    { return QSqlRelationalTableModel::data( item, role ); break; }
 }
}