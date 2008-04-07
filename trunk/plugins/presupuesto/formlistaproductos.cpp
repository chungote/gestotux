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
#include "formlistaproductos.h"
#include <QSqlRecord>
#include <QTableView>
#include <QSqlRelationalDelegate>

FormListaProductos::FormListaProductos(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, Qt::Dialog ), Ui::FormListaProductosBase()
{
	setupUi(this);
	this->setAttribute( Qt::WA_DeleteOnClose );
	this->setWindowTitle( "Listado de Productos" );

	modelo = new MTProductosPresupuesto( this );
	TVLista->setModel( modelo );
	TVLista->setItemDelegate( new QSqlRelationalDelegate( TVLista ) );
	TVLista->hideColumn( 0 );
	TVLista->hideColumn( 1 );

	connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( close() ) );
	connect( PBAgregar, SIGNAL( clicked() ), this, SLOT( agregar() ) );
	connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminar() ) );
	connect( PBAceptar, SIGNAL( clicked() ), this, SLOT( aceptar() ) );

	PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
	PBAceptar->setIcon( QIcon( ":/imagenes/aplicar.png" ) );
	PBCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
}

FormListaProductos::~FormListaProductos()
{
}




/*!
    \fn FormListaProductos::agregar()
 */
void FormListaProductos::agregar()
{
 modelo->insertRecord( -1, QSqlRecord() );
}


/*!
    \fn FormListaProductos::eliminar()
 */
void FormListaProductos::eliminar()
{
    /// @todo implement me
}


/*!
    \fn FormListaProductos::aceptar()
 */
void FormListaProductos::aceptar()
{
    /// @todo implement me
}
