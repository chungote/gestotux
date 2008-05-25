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
#include <QSqlError>
#include <QSqlRecord>
#include "mcaravanadueno.h"

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
		CBCliente->setCurrentIndex( CBCliente->findText( movimiento->getVendedor().second ) );
		// Coloco el establecimiento de destino
		CBEstablecimientoDestino->setCurrentIndex( CBCliente->findText( movimiento->getEstablecimientoDestino().second ) );
		break;
	}
	case venta:
	{
		// Pongo el comprado
		CBCliente->setCurrentIndex( CBCliente->findText( movimiento->getComprador().second ) );
		// Pongo el establecimiento de origen
		CBEstablecimientoOrigen->setCurrentIndex( CBCliente->findText( movimiento->getEstablecimientoOrigen().second ) );
		break;
	}
	case mudanza:
	{
		// Coloco el establecimiento de destino
		CBEstablecimientoDestino->setCurrentIndex( CBCliente->findText( movimiento->getEstablecimientoDestino().second ) );
		// Pongo el establecimiento de origen
		CBEstablecimientoOrigen->setCurrentIndex( CBCliente->findText( movimiento->getEstablecimientoOrigen().second ) );
		break;
	}
	case stock:
	{
		// Pongo el establecimiento de destino
		CBEstablecimientoDestino->setCurrentIndex( CBCliente->findText( movimiento->getEstablecimientoDestino().second ) );
		break;
	}
	default:
	{
		break;
	}
 } // fin switch de tipo de accion
 LEDTA->setText( movimiento->getDTA() );
 LEGuia->setText( movimiento->getNumeroGuia() );
 CBCategoria->setCurrentIndex( CBCategoria->findText( movimiento->getCategoria().second ) );
 QSqlQuery cola( QString( "SELECT especial FROM car_categorias WHERE nombre = '%1'" ).arg( movimiento->getCategoria().first ) );
 if( cola.next() )
 {
  if( cola.record().value(0).toBool() )
  {
	// Tengo que mostrar y cargar el tema de la cantidad de menchos
	SBCantidadAnimales->setValue( movimiento->getCantidadAnimales() );
  }
  else
  {
  	// Cargo las caravanas
	if( !model->cargarCaravanasTri( movimiento->getTri() ) )
	{
//		model->clear();
	}
  }
 }
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
