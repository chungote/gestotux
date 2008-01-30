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
#include "mclientes.h"

MClientes::MClientes( QObject *parent )
 : QSqlTableModel( parent )
{
 setTable( "clientes" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Apellido" );
 setHeaderData( 2, Qt::Horizontal, "Nombre" );
 setHeaderData( 3, Qt::Horizontal, "Direccion" );
 setHeaderData( 4, Qt::Horizontal, "Telefono/Celular" );
}


MClientes::~MClientes()
{
}


QVariant MClientes::data(const QModelIndex& idx, int role) const
{
    return QSqlTableModel::data(idx, role);
}

Qt::ItemFlags MClientes::flags(const QModelIndex& index) const
{
    return QSqlTableModel::flags(index);
}

bool MClientes::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlTableModel::setData(index, value, role);
}

