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
#include "formagregarventa.h"
#include "mproductostotales.h"
#include "dproductostotales.h"
#include "emcliente.h"
#include <QTableView>

FormAgregarVenta::FormAgregarVenta ( QWidget* parent, Qt::WFlags fl )
: EVentana ( parent, fl ), Ui::FormAgregarVentaBase()
{
	setupUi( this );
	this->setObjectName( "formagregarcompra" );
	this->setWindowTitle( "Agregar Venta" );
	this->setWindowIcon( QIcon(":/imagenes/venta.png" ) );

	PBAgregarProducto->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBAgregarProducto->setText( "Agregar Producto" );
	PBEliminarProducto->setText( "Eliminar Producto" );
	PBEliminarProducto->setIcon( QIcon( ":/imagenes/eliminar.png" ) );

	connect( PBAgregarProducto, SIGNAL( clicked() ), this, SLOT( agregarProducto() ) );
	connect( PBEliminarProducto, SIGNAL( clicked() ), this, SLOT( eliminarProducto() ) );

	// Inicio los modelos
	CBCliente->setModel( new EMCliente( CBCliente ) );
	CBCliente->setModelColumn( 1 );

	// Lista de Precios
	/*CBListaPrecio->setModel( new MListaPrecio( CBListaPrecio ) );
	CBListaPrecio->setModelColumn( 1 );

	// Forma de Pago
	CBFormaPago->setModel( );
	CBFormaPago->setModelColumn( );*/

	// Modelo del tableview
	TVProductos->setModel( new MProductosTotales( TVProductos ) );
	TVProductos->setItemDelegate( new DProductosTotales( TVProductos ) );
	TVProductos->setAlternatingRowColors( true );

}

FormAgregarVenta::~FormAgregarVenta()
{
}
