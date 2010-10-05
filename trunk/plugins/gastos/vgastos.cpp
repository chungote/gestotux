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
#include "vgastos.h"

#include "mgasto.h"
#include "dgastos.h"
#include <QPushButton>
#include <QTableView>
#include <QSqlRelationalDelegate>
#include <QAction>

VGastos::VGastos( QWidget* parent )
: EVLista( parent )
{
 setObjectName( "vistaGastos" );
 setWindowTitle( "Visor de Gastos" );
 setWindowIcon( QIcon(":/imagenes/gasto.jpg" ) );

 // Redirijo la opcion de agregar al plugin
 ActAgregar->disconnect();
 connect( ActAgregar, SIGNAL( triggered() ), this, SLOT( agregarGasto() ) );

 modelo = new MGasto( this, true );
 modelo->select();
 while( modelo->canFetchMore() ) { modelo->fetchMore(); }

 vista->setModel( modelo );
 vista->hideColumn( 0 );
 vista->hideColumn( 5 );
 vista->setItemDelegate( new DGastos( vista ) );

 vista->resizeColumnsToContents();
 QAction *ActCategorias = new QAction( this );
 ActCategorias->setText( "Categorias" );
 ActCategorias->setIcon( QIcon( ":/imagenes/categorias.png" ) );
 ActCategorias->setStatusTip( "Muestra las distintas categorias de gastos disponibles" );
 connect( ActCategorias, SIGNAL( triggered() ), this, SLOT( mostrarCategorias() ) );

 addAction( ActAgregar );
 //addAction( ActEliminar );
 addAction( ActCategorias );
 addAction( ActCerrar );
}


VGastos::~VGastos()
{
}

void VGastos::antes_de_insertar(int row, QSqlRecord& record)
{ return; }

#include "formagregargasto.h"
/*!
    \fn VGastos::agregarGasto()
    Muestra la ventana de agregar gastos
 */
void VGastos::agregarGasto()
{ emit agregarVentana( new FormAgregarGasto() ); }

#include "vcategoriasgastos.h"
/*!
    \fn VGastos::mostrarCategorias()
    Muestra la ventana de cateogiras de gastos
 */
void VGastos::mostrarCategorias()
{ emit agregarVentana( new VCategoriasGastos() ); }
