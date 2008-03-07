/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar  						   *
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
#include "formagregarpresupuesto.h"

#include <QSqlQueryModel>
#include <QDate>
#include "formlistaproductos.h"

FormAgregarPresupuesto::FormAgregarPresupuesto(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::FormPresupuestoBase()
{
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	this->setObjectName( "FormAgregarPresupuesto" );
	LTitulo->setText( "Agregar Presupuesto" );
	
	connect( RBCliente, SIGNAL( toggled( bool ) ), CBCliente , SLOT( setEnabled( bool ) ) );
	connect( RBOtro   , SIGNAL( toggled( bool ) ), LEOtro    , SLOT( setEnabled( bool ) ) );
	connect( CkBTitulo, SIGNAL( toggled( bool ) ), LETitulo  , SLOT( setEnabled( bool ) ) );

	QAction *ActGuardar = new QAction( "Guardar", this );
	ActGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
	ActGuardar->setStatusTip( "Guarda el formulario de presupuesto actual y lo muestra ( Ctrl + g )" );
	ActGuardar->setShortcut( QKeySequence( "Ctrl+g" ) );
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );
	addAction( ActGuardar );

	QAction *ActCancelar = new QAction( "Cancelar", this );
	ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	ActCancelar->setStatusTip( "Cancela los cambios realizados y cierra la ventana" );
	ActCancelar->setShortcut( QKeySequence( "Ctrl+c" ) );
	connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( cancelar() ) );
	addAction( ActCancelar );

	QAction *ActProductos = new QAction( "Agregar productos", this );
	ActProductos->setIcon( QIcon( ":/imagenes/productos.png" ) );
	ActProductos->setStatusTip( "Inserta una lista de productos en el presupuesto" );
	ActProductos->setShortcut( QKeySequence( "Ctrl+p" ) );
	connect( ActProductos, SIGNAL( triggered() ), this, SLOT( listaProductos() ) );
	addAction( ActProductos );

	// Seteo la lista de clientes
	modeloClientes = new QSqlQueryModel( this );
	modeloClientes->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );
	
	CBCliente->setModel( modeloClientes );
	CBCliente->setModelColumn( 1 );
	CBCliente->setCurrentIndex( -1 );


	// Pongo la fecha actual
	dEFecha->setDate( QDate::currentDate() );
}

FormAgregarPresupuesto::~FormAgregarPresupuesto()
{
}


/*!
    \fn FormAgregarPresupuesto::listaProductos()
	Metodo que agrega o modifica la lista de productos que se van a colocar en el presupuesto
 */
void FormAgregarPresupuesto::listaProductos()
{
  FormListaProductos *f = new FormListaProductos( this );
  f->show();
    /// @todo implementar señales y demas mugres
}


/*!
    \fn FormAgregarPresupuesto::cancelar()
	Elimina datos temporales y cierra el formulario
 */
void FormAgregarPresupuesto::cancelar()
{
    /// @todo Verificar el cierre de este formulario por asociaciones con otras tablas
    this->close();
}
