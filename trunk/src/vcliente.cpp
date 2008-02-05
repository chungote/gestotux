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
#include "gestotux.h"
#include <QHeaderView>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>


VCliente::VCliente( QWidget *parent )
 : EVentana( parent )
{
 nombre_ventana = "lista_clientes";
 this->setAttribute( Qt::WA_DeleteOnClose );
 setObjectName( "Listado de Clientes" );

 modelo = new MClientes( this );
 modelo->setEditStrategy( QSqlTableModel::OnFieldChange );

 vista = new QTableView( this );
 QGridLayout *layout = new QGridLayout( this );
 layout->addWidget( vista );
 vista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
 vista->setTextElideMode( Qt::ElideRight );
 vista->setSelectionBehavior( QAbstractItemView::SelectRows );
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 modelo->select();

 crearAcciones();

}


void VCliente::crearAcciones()
{
 ActAgregar = new QAction( "Agregar", this );
 ActAgregar->setStatusTip( "Agregar nuevo cliente" );
 ActAgregar->setIcon( QIcon( ":/imagenes/add_user.png" ) );
 connect( ActAgregar, SIGNAL( triggered() ), this, SLOT( agregar() ) );

 ActEliminar = new QAction( "Eliminar", this );
 ActEliminar->setStatusTip( "Elimina el usuario seleccionado" );
 ActEliminar->setIcon( QIcon( ":/imagenes/delete_user.png" ) );
 connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminar() ) );

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setStatusTip( "Cierra la lista de clientes" );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 connect( ActCerrar, SIGNAL( triggered() ), gestotux::formCen(), SLOT( cerrarActivo() ) );


 addAction( ActAgregar );
 addAction( ActEliminar );
 addAction( ActCerrar );

}


VCliente::~VCliente()
{
}


/*!
    \fn VCliente::agregar()
 */
void VCliente::agregar()
{
 QSqlRecord registro = modelo->record();
 registro.setValue( 1, "" );
 registro.setValue( 2, "" );
 registro.setValue( 3, "" );
 registro.remove( 0 );
 if( !modelo->insertRecord( -1, registro ) )
 {
  qWarning( "Error al insertar el registro" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modelo->lastError().type() ).arg( modelo->lastError().number() ).arg( modelo->lastError().text() ).toLocal8Bit() );
 }
}


/*!
    \fn VCliente::eliminar()
 */
void VCliente::eliminar()
{
 //Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = vista->selectionModel();
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
