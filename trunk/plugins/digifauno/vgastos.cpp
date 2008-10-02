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
#include "digifauno.h"
#include "dgastos.h"
#include <QPushButton>
#include <QTableView>
#include <QSqlRelationalDelegate>

VGastos::VGastos( QWidget* parent )
: EVLista( parent, false )
{
 setObjectName("vistaGastos");
 setWindowTitle(  "Visor de Gastos" );

 ActAgregar->disconnect();
 DigiFauno *digifauno = qobject_cast<DigiFauno *>(parent);
 connect( ActAgregar, SIGNAL( clicked() ), digifauno, SLOT( agregar_gasto() ) );


 modelo = new MGasto( this );
 modelo->select();
 while( modelo->canFetchMore() )
 {
  modelo->fetchMore();
 }

 vista->setModel( modelo );
 vista->hideColumn( 0 );
 //vista->hideColumn( 1 );
 vista->setItemDelegate( new DGastos( vista ) );


 vista->resizeColumnsToContents();

 addAction( ActAgregar );
 addAction( ActEliminar );
 addAction( ActCerrar );
}


VGastos::~VGastos()
{
}


void VGastos::antes_de_insertar(int row, QSqlRecord& record)
{
 return;
}

