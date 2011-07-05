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
#include "vventas.h"

#include "eactcerrar.h"
#include "MFactura.h"
#include <QIcon>
#include <QTableView>
#include "MVFacturas.h"
#include <QMessageBox>


VVentas::VVentas(QWidget *parent)
 : EVLista(parent)
{
    this->setObjectName( "ListaFacturas" );
    this->setWindowTitle( "Lista de Facturas" );
    this->setWindowIcon( QIcon( ":/imagenes/factura.png" ) );

    this->modelo = new MVFacturas( this->vista );
    this->vista->setModel( this->modelo );

    this->vista->hideColumn( 0 );
    this->vista->setAlternatingRowColors( true );
    this->modelo->select();

    QAction *ActPagar = new QAction( this );
    ActPagar->setText( "Pagar" );
    ActPagar->setIcon( QIcon( ":/imagenes/pagarfactura.png" ) );
    ActPagar->setStatusTip( "Genera un recibo por las facturas seleccionadas." );
    connect( ActPagar, SIGNAL( triggered() ), this, SLOT( pagar() ) );

    QAction *ActAnular = new QAction( this );
    ActAnular->setText( "Anular" );
    ActAnular->setIcon( QIcon( ":/imagenes/anularfactura.png" ) );
    ActAnular->setStatusTip( "Anula las facturas seleccionadas" );
    connect( ActAnular, SIGNAL( triggered() ), this, SLOT( anular() ) );

    ActAgregar->setIcon( QIcon( ":/imagenes/facturanueva.png" ) );

    this->addAction( ActAgregar );
    this->addAction( ActPagar );
    this->addAction( ActAnular );
    this->addAction( new EActCerrar( this ) );
}


#include "formagregarventa.h"
void VVentas::agregar()
{ emit agregarVentana( new FormAgregarVenta() ); }

void VVentas::buscar()
{}

void VVentas::eliminar()
{ return; }

void VVentas::imprimir()
{ return; }

void VVentas::modificar()
{ return; }

void VVentas::anular()
{
    // Busco todos los IDs a anular
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() < 1 ) {
        QMessageBox::warning( this, "Seleccione un item",
                        "Por favor, seleccione al menos un item para anular",
                        QMessageBox::Ok );
        return;
    }
    return;
}

void VVentas::pagar()
{
    // Busco todos los IDs a pagar
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() < 1 ) {
        QMessageBox::warning( this, "Seleccione un item",
                        "Por favor, seleccione al menos un item para pagar.",
                        QMessageBox::Ok );
        return;
    }
    return;
}