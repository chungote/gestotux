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
#include "vpresupuesto.h"
#include "mpresupuesto.h"
#include <QTableView>
#include "formagregarpresupuesto.h"

VPresupuesto::VPresupuesto(QWidget *parent)
 : EVLista(parent)
{
 setObjectName( "visorPresupuestos" );
 setWindowTitle( "Presupuestos Anteriores" );
 setWindowIcon( QIcon( ":/imagenes/anteriores.png" ) );
 modelo = new MPresupuesto( this );
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 vista->hideColumn( 5 );
 modelo->select();

 addAction( ActAgregar );
 addAction( ActModificar );
 addAction( ActEliminar );
 addAction( ActImprimir );
 addAction( ActCerrar );
}


VPresupuesto::~VPresupuesto()
{
}


void VPresupuesto::agregar()
{
 emit agregarVentana( new FormAgregarPresupuesto() );
 this->close();
}

void VPresupuesto::antes_de_insertar(int /*row*/, QSqlRecord& /*record*/)
{
}

void VPresupuesto::buscar()
{
   // EVLista::buscar();
}

void VPresupuesto::cerrar()
{
    EVLista::cerrar();
}

void VPresupuesto::eliminar()
{
    //EVLista::eliminar();
}

void VPresupuesto::imprimir()
{
    //EVLista::imprimir();
}

void VPresupuesto::modificar()
{
   // EVLista::modificar();
}

