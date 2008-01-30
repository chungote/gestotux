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
#include "vrecibos.h"
#include "mrecibo.h"
#include "hicomp.h"
#include "formmodificarrecibo.h"
#include "formagregarrecibo.h"
#include "drecibo.h"
#include <QTableView>
#include <QAction>
#include <QToolBar>
#include <QHeaderView>
#include <QGridLayout>
#include <QMessageBox>
#include <QModelIndex>


VRecibos::VRecibos( QWidget *parent )
 : QWidget( parent )
{
 setObjectName( "Recibos Emitidos" );
 this->setAttribute( Qt::WA_DeleteOnClose );

 modelo = new MRecibo( this );

 vista = new QTableView( this );
 QGridLayout *layout = new QGridLayout( this );
 layout->addWidget( vista );
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 vista->setItemDelegate( new DRecibo( vista ) );

 modelo->select();

 vista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
 vista->setTextElideMode( Qt::ElideRight );
 vista->setSelectionBehavior( QAbstractItemView::SelectRows );

 ActVer = new QAction( "Ver", this );
 ActVer->setIcon( QIcon( ":/imagenes/ver.png" ) );
 ActVer->setStatusTip( "Ver el primer recibo que se encuentra seleccionado" );
 connect( ActVer, SIGNAL( triggered() ), this, SLOT( ver() ) );

 ActAgregar = new QAction( "Agregar", this );
 ActAgregar->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
 ActAgregar->setStatusTip( "Genera un nuevo recibo" );
 connect( ActAgregar, SIGNAL( triggered() ), this, SLOT( agregar() ) );

 ActModificar = new QAction( "Modificar", this );
 ActModificar->setIcon( QIcon( ":/imagenes/editar.png" ) );
 ActModificar->setStatusTip( "Modifica el recibo seleccionado" );
 connect( ActModificar, SIGNAL( triggered() ), this, SLOT( modificar() ) );

 ActEliminar = new QAction( "Eliminar", this );
 ActEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
 ActEliminar->setStatusTip( "Elimina el recibo seleccionado" );
 connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminar() ) );

  ActImprimir = new QAction( "Imprimir", this );
  ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
  ActImprimir->setStatusTip( "Imprime el recibo actual" );
  connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 ActCerrar->setStatusTip( "Cierra esta ventana" );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

 addAction( ActVer );
 addAction( ActAgregar );
 addAction( ActModificar );
 addAction( ActEliminar );
 addAction( ActImprimir );
 addAction( ActCerrar );
}


VRecibos::~VRecibos()
{
}


void VRecibos::agregar()
{
 FormAgregarRecibo *f = new FormAgregarRecibo();
 HiComp::tabs()->addTab( f, f->objectName() );
}

void VRecibos::modificar()
{
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedRows();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un recibo",
                   "Por favor, seleccione un recibo para ver",
                   QMessageBox::Ok );
   return;
 }
 QModelIndex indice;
 ///@todo Ver esto!!!
 /*FormModificarRecibo *f = new FormModificarRecibo( gestotux::formCen() );
 gestotux::formCen()->agregarVentana( f );
 f->cargarDatos( indices[0], modelo );*/
}


void VRecibos::ver()
{
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedRows();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un recibo",
                   "Por favor, seleccione un recibo para ver",
                   QMessageBox::Ok );
   return;
 }
 QModelIndex indice;
 foreach( indice, indices )
 {
   if ( indice.isValid() )
   {
///@todo    gestotux::formCen()->agregarRecibo( indice.model()->data( indice.model()->index( indice.row(), 0 ), Qt::DisplayRole ).toInt() );
   }
 }
}



/*!
    \fn VRecibos::eliminar()
 */
void VRecibos::eliminar()
{
//Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedRows();
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
	foreach( indice, indices )
	{
		if( indice.isValid() )
		{
			modelo->removeRow( indice.row() );
		}
	}
 }
 return;
}

