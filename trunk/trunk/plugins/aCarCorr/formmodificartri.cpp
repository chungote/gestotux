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
#include "formmodificartri.h"
#include <QSqlQuery>


FormModificarTri::FormModificarTri(QWidget *parent, int accion, int id_tri )
: FormMovimiento( parent, 0, accion )
{
 movimiento = new EMovimiento( this );
 movimiento->cargarMovimiento( id_tri );
 // Cargo los datos en su correspondiente lugar
 dEFecha->setDate( movimiento->getFecha() );
 LETRI->setText( QString( "%1" ).arg( movimiento->getTri() ) );
 switch( accion )
 {
	case compra:
	{
		// Coloco el vendedor
		// Coloco el establecimiento de destino
		break;
	}
	case venta:
	{
		// Pongo el comprado
		// Pongo el establecimiento de origen
		break;
	}
	case mudanza:
	{
		// Coloco el establecimiento de destino
		// Pongo el establecimiento de origen
		break;
	}
	case stock:
	{
		// Pongo el establecimiento de destino
		break;
	}
	default:
	{
		break;
	}
 } // fin switch de tipo de accion
}


FormModificarTri::~FormModificarTri()
{
}


/*!
    \fn FormModificarTri::guardar
 */
void FormModificarTri::guardar()
{
    /// @todo implement me
}
