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

#include "vcajas.h"

#include <QIcon>
#include <QAction>
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>

#include "mcajas.h"
#include "actretirocaja.h"
#include "actingresocaja.h"
#include "acttransferir.h"
#include "formtransferir.h"

#include "FormAgregarCaja.h"

VCajas::VCajas(QWidget *parent) :
    EVLista(parent)
{
    this->setObjectName( "visorCajas" );
    this->setWindowTitle( "Cajas" );
    this->setWindowIcon( QIcon( ":/imagenes/caja.png" ) );

    modelo = new MCajas( this );
    vista->setModel( modelo );
    vista->setAlternatingRowColors( true );
    vista->hideColumn(0);
    vista->setSortingEnabled( true );
    modelo->select();

    connect( vista, SIGNAL( doubleClicked ( const QModelIndex & ) ), this, SLOT( resumen( const QModelIndex & ) ) );

    ActIngreso = new ActIngresoCaja( this );
    ActEgreso = new ActRetiroCaja( this );
    ActTransferire = new ActTransferir( this );

    ActResumen = new QAction( this );
    ActResumen->setText( "Resumen" );
    ActResumen->setIcon( QIcon( ":/imagenes/cajaresumen.png" ) );
    ActResumen->setToolTip("Muestra el resumen de las operaciones de caja desde el ultimo cierre" );
    connect( ActResumen, SIGNAL( triggered() ), this, SLOT( resumen() ) );

    addAction( ActAgregar );
    addAction( ActEgreso );
    addAction( ActIngreso );
    addAction( ActTransferire );
    addAction( ActResumen );
    //addAction( ActEliminar );
    addAction( ActCerrar );
}


void VCajas::agregar( bool autoeliminarid ) {
   (void)autoeliminarid;
   FormAgregarCaja *f = new FormAgregarCaja( this );
   f->exec();
   modelo->select();
}

#include "FormRetiroIngreso.h"

void VCajas::retiro() {
   FormRetiroIngreso *r = new FormRetiroIngreso( this );
   r->exec();
   modelo->select();
}

void VCajas::ingreso() {
    FormRetiroIngreso *r = new FormRetiroIngreso( this, FormRetiroIngreso::Ingreso );
    r->exec();
    modelo->select();
}

void VCajas::transferir()
{
   FormTransferir *f = new FormTransferir();
   f->adjustSize();
   f->exec();
   modelo->select();
}

#include "vresumencaja.h"
void VCajas::resumen()
{
    if( vista->selectionModel()->selectedRows().isEmpty() ) {
        QMessageBox::warning( this, "Error", "Por favor, seleccione una caja para ver su resumen" );
        return;
    }
    QModelIndex idx = vista->selectionModel()->selectedRows().first();
    int id_caja = idx.model()->data( idx.model()->index( idx.row(), 0 ), Qt::EditRole ).toInt();
    VResumenCaja *vr = new VResumenCaja( this );
    vr->setearCaja( id_caja );
    emit agregarVentana( vr );
}
