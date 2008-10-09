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
#include "vcompras.h"

#include "mcompra.h"
#include <QTableView>
#include "digifauno.h"
#include <QPushButton>

VCompras::VCompras(QWidget *parent)
 : EVLista( parent )
{
 setObjectName( "lista_compras" );
 setWindowTitle( "Lista de compras realizadas" );
 setWindowIcon( QIcon(":/imagenes/compras.jpg" ) );
 modelo = new MCompra( this, true );
 vista->setModel( modelo );
 modelo->select();
 vista->hideColumn( 0 );
 vista->resizeColumnsToContents();

 ActAgregar->disconnect( SIGNAL( triggered() ), this, SLOT( agregar() ) );
 DigiFauno *digifauno = qobject_cast<DigiFauno *>(parent);
 connect( ActAgregar, SIGNAL( triggered() ), digifauno, SLOT( agregarCompra() ) );
 addAction( ActAgregar );
 addAction( ActModificar );
 addAction( ActEliminar );
 addAction( ActCerrar );
}


VCompras::~VCompras()
{
}


void VCompras::antes_de_insertar(int row, QSqlRecord& record)
{
}

