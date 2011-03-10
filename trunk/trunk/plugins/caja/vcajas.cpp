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
    modelo->select();

    //connect( vista, SIGNAL( doubleClicked ( const QModelIndex & ) ), this, SLOT( modificar( const QModelIndex & ) ) );

    addAction( ActAgregar );
    addAction( new ActRetiroCaja( this ) );
    addAction( new ActIngresoCaja( this ) );
    addAction( new ActTransferir( this ) );
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
