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
#include "vproductos.h"
#include "mproductos.h"
#include "digifauno.h"
#include "dproductos.h"

#include <QTableView>
#include <QPushButton>
#include <QBoxLayout>
#include <QSqlRelationalDelegate>
#include <QIcon>
#include <QHeaderView>
#include <QSqlRecord>

VProductos::VProductos( QWidget *parent )
 : EVLista(parent, false )
{
 setWindowIcon( QIcon( ":/imagenes/productos.jpg" ) );
 setWindowTitle( "Listado de productos" );

 modelo = new MProductos( this );

 vista->setModel( modelo );
 vista->hideColumn( 0 );
 vista->setItemDelegate( new DProductos( vista ) );

 modelo->setSort( 2, Qt::AscendingOrder );
 modelo->select();

 vista->resizeColumnsToContents();
 vista->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
 vista->setAlternatingRowColors( true );
 vista->setSortingEnabled( true );

 addAction( ActAgregar );
 addAction( ActEliminar );
 addAction( ActCerrar );
}


VProductos::~VProductos()
{
}

/*!
    \fn VProductos::antes_de_insertar(  int row, QSqlRecord &registro )
 */
void VProductos::antes_de_insertar(  int row, QSqlRecord &registro )
{
 registro.setValue( "descripcion", "" );
 registro.setValue( "marca", "" );
 registro.setValue( "precio", 0 );
}


/*!
    \fn VProductos::closeEvent( QCloseEvent * event )
 */
void VProductos::closeEvent( QCloseEvent * event )
{
 EVLista::closeEvent( event );
}
