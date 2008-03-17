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
#include "vcategorias.h"

#include "mcategoria.h"
#include <QTableView>
#include <QSqlRecord>

VCategorias::VCategorias( QWidget *parent )
 : EVLista( parent )
{
 setAttribute( Qt::WA_DeleteOnClose );
 setObjectName( "car_categorias" );
 modelo = new MCategoria(this);
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 modelo->select();

 addAction( ActAgregar );
 addAction( ActEliminar );
 addAction( ActCerrar );
}


VCategorias::~VCategorias()
{
}


void VCategorias::antes_de_insertar(int row, QSqlRecord& record)
{
 record.value( 1 ).setValue( QString(" ") );
 record.remove( 0 );
 return;
}

void VCategorias::eliminar()
{
	// Verificar que no existan caravanas con esta categoria
    EVLista::eliminar();
}

