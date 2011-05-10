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

#include "MItemPresupuesto.h"

MItemPresupuesto::MItemPresupuesto(QObject *parent) :
    QSqlRelationalTableModel(parent) {
    inicializar();
    relacionar();
}


void MItemPresupuesto::inicializar() {
    setTable( "item_presupuesto" );
    setHeaderData( 0, Qt::Horizontal, "#Orden" );
    setHeaderData( 1, Qt::Horizontal, "#Presupuesto" );
    setHeaderData( 2, Qt::Horizontal, "Cantidad" );
    setHeaderData( 3, Qt::Horizontal, "Texto" );
    setHeaderData( 4, Qt::Horizontal, "Precio Unitario" );
    setHeaderData( 5, Qt::Horizontal, "#Producto" );

}

void MItemPresupuesto::relacionar() {

}
