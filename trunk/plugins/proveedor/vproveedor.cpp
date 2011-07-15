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
#include "vproveedor.h"
#include "mproveedor.h"
#include "dproveedor.h"
#include <QTableView>
#include <QAction>
#include "EReporte.h"

VProveedor::VProveedor( QWidget *parent )
 : EVLista( parent )
{
 setObjectName( "ListaProveedores" );
 setWindowTitle( "Proveedores" );
 setWindowIcon( QIcon( ":/imagenes/proveedores.jpg" ) );
 modelo = new MProveedor( this );
 vista->setModel( modelo );
 vista->hideColumn( 0 ); // oculta el ID
 vista->setItemDelegate( new DProveedor( vista ) );
 modelo->sort( 2, Qt::AscendingOrder );
 modelo->select();
 vista->setSortingEnabled( true );

 QAction *ActListado = new QAction( this );
 ActListado->setText( "Listado" );
 ActListado->setStatusTip( "Imprime la lista de todos los proveedores" );
 ActListado->setIcon( QIcon( ":/imagenes/listadoproveedores.png" ) );
 connect( ActListado, SIGNAL(triggered() ), this, SLOT( listado() ) );

 addAction( ActAgregar );
 addAction( ActEliminar );
 addAction( ActListado );
 addAction( ActCerrar );
}


VProveedor::~VProveedor()
{
}

/*!
    \fn VProveedor::antes_de_insertar( int row, QSqlRecord & record )
 */
void VProveedor::antes_de_insertar( int /*row*/, QSqlRecord & /*record*/ )
{return;}


/*!
    \fn VProveedor::eliminar()
 */
void VProveedor::eliminar()
{
 qWarning( "Error, el eliminar un proveedor puede causar perdida de datos" );
 return;
}

/*!
 * \fn VProveedor::listado()
 * Muestra el listado de proveedores
 */
void VProveedor::listado()
{
    EReporte *rep = new EReporte( 0 );
    rep->especial( "ListadoProveedores", ParameterList() );
    if( !rep->hacer( ParameterList(), true ) ) {
        qDebug( "Hubo un error al intentar hacer el reporte" );
    }
    delete rep;
}
