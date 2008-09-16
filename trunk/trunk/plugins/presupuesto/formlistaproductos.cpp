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
#include "formlistaproductos.h"
#include <QSqlRecord>
#include <QTableView>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>

FormListaProductos::FormListaProductos(QWidget* parent, Qt::WFlags fl)
: EVentana( parent, fl ), Ui::FormListaProductosBase()
{
	setupUi(this);
	this->setAttribute( Qt::WA_DeleteOnClose );
	this->setWindowTitle( "Listado de Productos" );

	modelo = new MTProductosPresupuesto( this );
	TVLista->setModel( modelo );
	TVLista->setItemDelegate( new QSqlRelationalDelegate( TVLista ) );
	TVLista->hideColumn( 0 );
	TVLista->hideColumn( 1 );

	connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( hide() ) );
	connect( PBAgregar, SIGNAL( clicked() ), this,  SLOT( agregar() ) );
	connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminar() ) );
	connect( PBAceptar, SIGNAL( clicked() ), this, SIGNAL( agregarTabla() ) );

	PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
	PBAceptar->setIcon( QIcon( ":/imagenes/aplicar.png" ) );
	PBCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );

	adjustSize();
	groupBox->setVisible( PBMas->isChecked() );
	verificarProductos();
}

FormListaProductos::~FormListaProductos()
{
 delete modelo;
}




/*!
    \fn FormListaProductos::agregar()
 */
void FormListaProductos::agregar()
{
 modelo->insertRecord( -1, modelo->record() );
}


/*!
    \fn FormListaProductos::eliminar()
 */
void FormListaProductos::eliminar()
{
    /// @todo implement me
}





/*!
    \fn FormListaProductos::modelo() const
 */
MTProductosPresupuesto  * FormListaProductos::getModelo() const
{
 return modelo;
}


/*!
    \fn FormListaProductos::tituloTabla() const
 */
QString FormListaProductos::tituloTabla() const
{
 if( CkBTitulo->checkState() == Qt::Checked )
 {
   return LETituloTabla->text();
 }
 else
 {
   return QString();
 }
}


/*!
    \fn FormListaProductos::cabeceraColumnas() const
 */
bool FormListaProductos::cabeceraColumnas() const
{
 return CkBCabeceras->checkState();
}


/*!
    \fn FormListaProductos::verificarProductos()
 */
void FormListaProductos::verificarProductos()
{
 QSqlQuery cola( "SELECT COUNT(id) FROM producto" );
 if( cola.next() )
 {
	if( cola.record().value(0).toInt() <= 0 )
	{
		PBAgregar->setEnabled( false );
		PBEliminar->setEnabled( false );
		PBMas->setEnabled( false );
		PBAceptar->setEnabled( false );
	}
 }
}
