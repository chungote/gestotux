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
 : QSqlRelationalTableModel( parent )
{
 setTable( "clientes" );
/*
-- Describe CLIENTES
CREATE TABLE clientes (
    "id" INTEGER,
    "razon_social" TEXT NOT NULL,
    "nombre" TEXT NOT NULL,
    "segundo" TEXT,
    "apellido" TEXT,
    "calle" TEXT,
    "numero" INTEGER,
    "piso" INTEGER,
    "depto" INTEGER,
    "ciudad" TEXT,
    "codigo_postal" TEXT,
    "provincia" TEXT,
    "pais" TEXT,
    "tel_fijo" TEXT,
    "tel_celular" TEXT,
    "fax" TEXT,
    "email" TEXT,
    "comprobante_email" INTEGER,
    "id_lista_precio" INTEGER,
    "ctacte" INTEGER )
*/
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Razon Social" );
 setHeaderData( 2, Qt::Horizontal, "Nombre" );
 setHeaderData( 3, Qt::Horizontal, "Segundo Nombre" );
 setHeaderData( 4, Qt::Horizontal, "Apellido" );
 setHeaderData( 5, Qt::Horizontal, "Calle" );
 setHeaderData( 6, Qt::Horizontal, "Numero" );
 setHeaderData( 7, Qt::Horizontal, "Piso" );
 setHeaderData( 8, Qt::Horizontal, "Depto" );
 setHeaderData( 9, Qt::Horizontal, "Ciudad" );
 setHeaderData( 10, Qt::Horizontal, "Codigo Postal" );
 setHeaderData( 11, Qt::Horizontal, "Provincia" );
 setHeaderData( 12, Qt::Horizontal, "Pais" );
 setHeaderData( 13, Qt::Horizontal, "Telefono" );
 setHeaderData( 14, Qt::Horizontal, "Celular" );
 setHeaderData( 15, Qt::Horizontal, "Fax" );
 setHeaderData( 16, Qt::Horizontal, "Em@il" );
 setHeaderData( 17, Qt::Horizontal, "EnviarComprobantexEmail" );
/* setHeaderData( 18, Qt::Horizontal, "Lista de precio" );
 setRelation( 18, QSqlRelation( "lista_precio", "id_lista_precio", "nombre" ) );*/
 setHeaderData( 19, Qt::Horizontal, "�CtaCte?" );
}


MClientes::~MClientes()
{
}
