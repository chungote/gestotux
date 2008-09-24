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
#include "vcategorias.h"

#include "mcategorias.h"
#include <QTableView>
#include <QSqlRecord>
#include "dcategoria.h"

VCategorias::VCategorias( QWidget *parent )
 : EVLista( parent )
{
 setWindowIcon( QIcon( ":/imagenes/categorias.gif" ) );
 setWindowTitle( "Listado de categorias" );
 modelo = new MCategorias( this );
 vista->setModel( modelo );
 modelo->select();
 vista->hideColumn( 0 );
 vista->setItemDelegate( new DCategoria( vista ) );
 vista->resizeColumnsToContents();
 vista->sortByColumn( 3 );

 addAction( ActAgregar );
 addAction( ActEliminar );
 addAction( ActCerrar );
}


VCategorias::~VCategorias()
{
}

/*!
    \fn VCategorias::antes_de_insertar( int row, QSqlRecord & record )
 */
void VCategorias::antes_de_insertar( int row, QSqlRecord & record )
{
 record.setValue( "nombre", "" );
 record.setValue( "tipo", 0 );
}
