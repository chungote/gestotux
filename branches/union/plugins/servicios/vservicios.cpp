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
#include "vservicios.h"

#include "mservicios.h"
#include "formasociarserviciocliente.h"
#include "formservicio.h"
#include "FormFacturarServicio.h"

#include <QTableView>
#include <QAction>
#include <QMenu>

VServicios::VServicios(QWidget *parent)
 : EVLista(parent)
{
 this->setObjectName( "visorServicios" );
 this->setWindowTitle( "Servicios" );
 this->setWindowIcon( QIcon( ":/imagenes/servicios.png" ) );

 modelo = new MServicios( this );

 vista->setModel( modelo );
 vista->setAlternatingRowColors( true );
 modelo->select();
 vista->hideColumn( 0 );
 vista->hideColumn( 2 );

 connect( vista, SIGNAL( doubleClicked ( const QModelIndex & ) ), this, SLOT( modificar( const QModelIndex & ) ) );

 addAction( ActAgregar );
 //addAction( ActEliminar );
 addAction( ActCerrar );
}


VServicios::~VServicios()
{
}


void VServicios::agregar( bool /*autoeliminarid*/ )
{
  emit agregarVentana( new FormServicio );
}

void VServicios::antes_de_insertar(int row, QSqlRecord& record)
{
    EVLista::antes_de_insertar(row, record);
}

void VServicios::aPdf()
{
    EVLista::aPdf();
}

void VServicios::buscar()
{
    EVLista::buscar();
}

void VServicios::eliminar()
{
    EVLista::eliminar();
}

void VServicios::email()
{
    EVLista::email();
}

void VServicios::imprimir()
{
    EVLista::imprimir();
}

void VServicios::modificar()
{
    EVLista::modificar();
}

/*!
    \fn VServicios::modificar( const QModelIndex &idx )
 */
void VServicios::modificar( const QModelIndex &/*idx*/ )
{
 // modifico el indice actual
 return;
}


/*!
    \fn VServicios::menuContextual( const QModelIndex &indice, QMenu *menu )
 */
void VServicios::menuContextual( const QModelIndex &indice, QMenu *menu )
{
 // Agrego las acciones que quiero que aparezcan en el menu
 QAction *ActNuevoCliente = new QAction( menu );
 ActNuevoCliente->setText( "Adherir Cliente" );
 ActNuevoCliente->setStatusTip( "Adhiere un cliente al servicio seleccionado en la lista" );
 connect( ActNuevoCliente, SIGNAL( triggered() ), this, SLOT( darAltaServicioCliente() ) );

 QAction *ActVerClientes = new QAction( menu );
 ActVerClientes->setText( "Ver Clientes adheridos" );
 ActVerClientes->setStatusTip( "Muestra la lista de clientes adheridos a este servicio" );
 connect( ActVerClientes, SIGNAL( triggered() ), this, SLOT( verClientesAdheridos() ) );

 QAction *ActGenerarFacturacion = new QAction( menu );
 ActGenerarFacturacion->setText( "Generar Facturacion" );
 ActGenerarFacturacion->setStatusTip( "Genera todas las facturas para el periodo que se desea cobrar automaticamente" );
 connect( ActGenerarFacturacion, SIGNAL( triggered() ), this, SLOT( generarFacturacion() ) );

 QAction *ActRecargos = new QAction( menu );
 ActRecargos->setText( "Administrar Recargos" );
 ActRecargos->setStatusTip( "Administra los recargos posibles para este servicio" );
 connect( ActRecargos, SIGNAL( triggered() ), this, SLOT( verRecargos() ) );

 ActAgregar->setText( "Agregar Servicio");
 menu->addAction( ActAgregar );
 menu->addAction( ActNuevoCliente );
 menu->addAction( ActVerClientes );
 menu->addSeparator();
 menu->addAction( ActGenerarFacturacion );
 menu->addAction( ActRecargos );
 indiceMenu = indice;
 return;
}


/*!
    \fn VServicios::darAltaServicioCliente()
 */
void VServicios::darAltaServicioCliente()
{
 // El item actual seleccionado es en el cual se pidio el menu
 // Obtengo el numero de servicio de la vista...
 int id_servicio = vista->model()->data( vista->model()->index( vista->currentIndex().row(), 0 ), Qt::EditRole ).toInt();
 FormAsociarServicioCliente *f = new FormAsociarServicioCliente( this, FormAsociarServicioCliente::Cliente );
 f->setIdServicio( id_servicio );
 f->exec();
}

#include "FormClientesAdheridos.h"
/*!
    \fn VServicios::verClientesAdheridos()
    LLama al formulario que muestra la lista de clientes que estan adheridos al servicio
 */
void VServicios::verClientesAdheridos()
{
 // Obtengo el numero de servicio de la vista...
 int id_servicio = vista->model()->data( vista->model()->index( vista->currentIndex().row(), 0 ), Qt::EditRole ).toInt();
 FormClientesAdheridos *f = new FormClientesAdheridos( this );
 f->setServicioInicial( id_servicio );
 emit agregarVentana( f );
}

#include "formrecargos.h"
/*!
    \fn VServicios::verRecargos()
    Llama al formulario que muestra los recargos por servicio
 */
void VServicios::verRecargos()
{
 // Obtengo el numero de servicio de la vista...
 int id_servicio = modelo->data( modelo->index( vista->currentIndex().row(), 0 ) ).toInt();
 // Muestro el formulario de recargos con el id seteado
 FormRecargos *f = new FormRecargos();
 f->setearId( id_servicio );
 emit agregarVentana( f );
}

/*!
 * @fn VServicios::generarFacturacion()
 */
void VServicios::generarFacturacion()
{
 // Obtengo el numero de servicio de la vista...
 int id_servicio = modelo->data( modelo->index( vista->currentIndex().row(), 0 ) ).toInt();
 // Muestro el formulario de recargos con el id seteado
 FormFacturarServicio *f  = new FormFacturarServicio();
 f->setearServicio( id_servicio );
 emit agregarVentana( f );
 /// @todo Generar algoritmia para la facturación de el servicio
}