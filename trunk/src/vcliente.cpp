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
 : EVLista( parent )
{
 setObjectName( "lista_clientes" );
 this->setAttribute( Qt::WA_DeleteOnClose );
 setWindowTitle( "Listado de Clientes" );

 modelo = new MClientes( this );
 modelo->setEditStrategy( QSqlTableModel::OnFieldChange );

 vista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
 vista->setTextElideMode( Qt::ElideRight );
 vista->setSelectionBehavior( QAbstractItemView::SelectRows );
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 modelo->select();

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
    \fn VCliente::antes_de_insertar( int row, QSqlRecord & record )
 */
void VCliente::antes_de_insertar( int row, QSqlRecord & record )
{
 record.setValue( "nombre", " " );
 record.setValue( "apellido", " " );
 record.setValue( "direccion", " " );
}
