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
#include "eregistroplugins.h"

#include <QApplication>
#include <QTableView>
#include <QGridLayout>
#include <QAction>
#include <QTableView>
#include <QHeaderView>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>


VCliente::VCliente( QWidget *parent )
 : EVLista( parent )
{
 setObjectName( "lista_clientes" );
 this->setAttribute( Qt::WA_DeleteOnClose );
 setWindowTitle( "Listado de Clientes" );
 setWindowIcon( QIcon( ":/imagenes/clientes.png" ) );

 mc = new MClientes( vista );
 modelo = 0;
 rmodelo = 0;
 vista->setModel( mc );
 mc->query().setForwardOnly( true );
 vista->hideColumn( mc->fieldIndex( "id" ) );
 vista->hideColumn( mc->fieldIndex( "nombre" ) );
 vista->hideColumn( mc->fieldIndex( "apellido" ) );
 vista->hideColumn( mc->fieldIndex( "piso" ) );
 vista->hideColumn( mc->fieldIndex( "depto" ) );
 vista->hideColumn( mc->fieldIndex( "provincia" ) );
 vista->hideColumn( mc->fieldIndex( "codigo_postal" ) );
 vista->hideColumn( mc->fieldIndex( "pais" ) );
 vista->hideColumn( mc->fieldIndex( "fax" ) );
 vista->hideColumn( mc->fieldIndex( "email" ) );
 vista->hideColumn( mc->fieldIndex( "comprobante_email" ) );
 vista->hideColumn( mc->fieldIndex( "ctacte" ) );
 vista->hideColumn( mc->fieldIndex( "id_estado_fiscal" ) );
 vista->setAlternatingRowColors( true );

 QAction *ActLista = new QAction( this );
 ActLista->setText( "Listado" );
 ActLista->setStatusTip( "Listado de clientes" );
 ActLista->setIcon( QIcon( ":/imagenes/listaclientes.png" ) );
 connect( ActLista, SIGNAL( triggered() ), this, SLOT( listadoClientes() ) );

 ActAgregar->setIcon( QIcon( ":/imagenes/add_user.png" ) );
 ActEliminar->setIcon( QIcon( ":/imagenes/delete_user.png" ) );

 ActBuscar->setCheckable( true );

 addAction( ActAgregar );
 addAction( ActModificar );
 addAction( ActEliminar );
 addAction( ActLista );
 addAction( ActBuscar );
 addAction( ActVerTodos );
 addAction( ActCerrar );
}

#include "formcliente.h"
/*!
    \fn VCliente::agregar( bool autoeliminarid )
 */
void VCliente::agregar( bool /*autoeliminarid*/ )
{
    FormCliente *f = new FormCliente( this, mc );
    f->agregar();
    emit agregarVentana( f );
}


/*!
  \fn VCliente::modificar()
 */
void VCliente::modificar()
{
    FormCliente *f = new FormCliente( this, mc );
    f->setearCliente( this->vista->selectionModel()->selectedRows().first() );
    emit agregarVentana( f );
}


#include "EReporte.h"
void VCliente::listadoClientes() {
    if( this->mc->rowCount() <= 0 ) {
        QMessageBox::warning( this, "Error", "No existe ningun cliente para imprimir un listado. No se imprimira nada" );
        return;
    }
    // Hago el listado de clientes
    EReporte *rep = new EReporte( this );
    rep->especial( "ListadoClientes", ParameterList() );
    if( !rep->hacer() ) {
        QMessageBox::warning( this, "Error", "No se pudo realizar el reporte" );
    }
}

#include "buscarcliente.h"
void VCliente::buscar()
{
    if( ActBuscar->isChecked() ) {
        this->b = new BuscarCliente( this, this->mc );
        emit agregarDockWidget( Qt::BottomDockWidgetArea, b );
    } else {
        if( this->b != 0 ) { this->b->hide(); }
    }
}

void VCliente::eliminar()
{
    QModelIndex idx = this->vista->selectionModel()->selectedRows().first();
    int id_cliente = this->mc->data( this->mc->index( idx.row(), 0 ), Qt::EditRole ).toInt();
    if( MClientes::tieneDatosRelacionados( id_cliente ) ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8("Eliminar este cliente generará perdida de relacion de datos." ) );
        return;
    }
    else
    {
        // ver como eliminar
        qWarning( "No implementado" );
    }
    return;
}

void VCliente::mostrarTodos()
{
    this->mc->select();
}
