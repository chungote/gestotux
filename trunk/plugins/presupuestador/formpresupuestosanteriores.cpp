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
#include "formpresupuestosanteriores.h"
#include "mpresupuestos.h"
#include "presupuestador.h"
#include "formmodificarpresupuesto.h"
#include "visorresumen.h"

#include <QMessageBox>
#include <QModelIndex>

FormPresupuestosAnteriores::FormPresupuestosAnteriores(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::FormPresupuestosAnterioresBase()
{
	setupUi(this);
	this->setAttribute( Qt::WA_DeleteOnClose );

	modelo = new MPresupuestos( this );
	TVPresupuestos->setModel( modelo );
	TVPresupuestos->hideColumn( 0 );
	TVPresupuestos->hideColumn( 4 );

	QAction *ActCerrar = new QAction( "Cerrar", this );
	ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

	QAction *ActVer = new QAction( "Ver", this );
	ActVer->setIcon( QIcon( ":/imagenes/ver.png" ) );
	connect( ActVer, SIGNAL( triggered() ), this, SLOT( mostrar() ) );

	QAction *ActModificar = new QAction( "Modificar", this );
	ActModificar->setIcon( QIcon( ":/imagenes/editar.png" ) );
	connect( ActModificar, SIGNAL( triggered() ), this, SLOT( modificar() ) );

	QAction *ActEliminar = new QAction( "Eliminar", this );
	ActEliminar->setIcon( QIcon( ":/imagenes/stop.png" ) );
	connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminar() ) );

	setWindowTitle( "Presupuestos Anteriores" );

	addAction( ActVer );
	addAction( ActModificar );
	addAction( ActEliminar );
	addAction( ActCerrar );
}

FormPresupuestosAnteriores::~FormPresupuestosAnteriores()
{
}



/*!
    \fn FormPresupuestosAnteriores::eliminar()
 */
void FormPresupuestosAnteriores::eliminar()
{
 //Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = TVPresupuestos->selectionModel();
 QModelIndexList indices = selectionModel->selectedIndexes();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un item",
                   "Por favor, seleccione un item para eliminar",
                   QMessageBox::Ok );
   return;
 }
 //Hacer dialogo de confirmacion..
 int ret;
 ret = QMessageBox::warning( this, "Esta seguro?",
                   QString( "Esta seguro de eliminar %1 item?").arg( indices.size() ),
                   "Si", "No" );
 if ( ret == 0 )
 {
	QModelIndex indice;
	foreach( indice, indices );
	{
		if( indice.isValid() )
		{
			modelo->removeRow( indice.row() );
		}
	}
 }
 return;
}


/*!
    \fn FormPresupuestosAnteriores::mostrar()
 */
void FormPresupuestosAnteriores::mostrar()
{
  //Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = TVPresupuestos->selectionModel();
 QModelIndexList indices = selectionModel->selectedIndexes();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un item",
                   "Por favor, seleccione un item para mostrar",
                   QMessageBox::Ok );
   return;
 }
 QModelIndex indice;
 foreach( indice, indices );
 {
	if( indice.isValid() )
	{
		///@todo Ver esto!
		visorResumen *v = new visorResumen( this );
		v->set_registro( modelo->data( modelo->index( indice.row(), 0 ), Qt::DisplayRole ).toInt() );
		presupuestador::tabs()->setCurrentWidget( presupuestador::tabs()->widget( presupuestador::tabs()->addWidget( v ) ) );
		this->close();
	}
 }
}


/*!
    \fn FormPresupuestosAnteriores::modificar()
 */
void FormPresupuestosAnteriores::modificar()
{
 //Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = TVPresupuestos->selectionModel();
 QModelIndexList indices = selectionModel->selectedIndexes();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un item",
                   "Por favor, seleccione un item para modificar",
                   QMessageBox::Ok );
   return;
 }
 QModelIndex indice = indices.at(0);
 FormModificarPresupuesto *f = new FormModificarPresupuesto( 0 );
 f->setId( modelo->data( modelo->index( indice.row(), 0 ), Qt::DisplayRole ).toInt() );
 f->show();
 this->close();
}
