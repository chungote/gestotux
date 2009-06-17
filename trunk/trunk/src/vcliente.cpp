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
#include "vcliente.h"

#include "mclientes.h"

#include <QTableView>
#include <QGridLayout>
#include <QAction>
#include <QTableView>
#include <QHeaderView>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>


VCliente::VCliente( QWidget *parent )
 : EVLista( parent )
{
 setObjectName( "lista_clientes" );
 this->setAttribute( Qt::WA_DeleteOnClose );
 setWindowTitle( "Listado de Clientes" );
 setWindowIcon( QIcon( ":/imagenes/clientes.png" ) );

 mc = new MClientes( vista );
 modelo = 0;
 rmodelo = 0;
 vista->setModel( mc );
 vista->hideColumn( mc->fieldIndex( "id" ) );
 vista->hideColumn( mc->fieldIndex( "nombre" ) );
 vista->hideColumn( mc->fieldIndex( "segundo" ) );
 vista->hideColumn( mc->fieldIndex( "apellido" ) );
 vista->hideColumn( mc->fieldIndex( "nombre" ) );
 vista->hideColumn( mc->fieldIndex( "piso" ) );
 vista->hideColumn( mc->fieldIndex( "depto" ) );
 vista->hideColumn( mc->fieldIndex( "provincia" ) );
 vista->hideColumn( mc->fieldIndex( "codigo_postal" ) );
 vista->hideColumn( mc->fieldIndex( "pais" ) );
 vista->hideColumn( mc->fieldIndex( "fax" ) );
 vista->hideColumn( mc->fieldIndex( "email" ) );
 vista->hideColumn( mc->fieldIndex( "comprobante_email" ) );
 vista->hideColumn( mc->fieldIndex( "lista_precio_id" ) );
 vista->setAlternatingRowColors( true );
 mc->select();


 ActAgregar->setIcon( QIcon( ":/imagenes/add_user.png" ) );
 ActEliminar->setIcon( QIcon( ":/imagenes/delete_user.png" ) );
 addAction( ActAgregar );
 addAction( ActEliminar );
 addAction( ActCerrar );
}


VCliente::~VCliente()
{
}

#include "formcliente.h"
/*!
    \fn VCliente::agregar( bool autoeliminarid )
 */
void VCliente::agregar( bool autoeliminarid )
{ emit agregarVentana( new FormCliente( this, mc ) ); }

