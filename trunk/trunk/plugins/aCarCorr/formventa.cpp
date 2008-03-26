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
#include "formventa.h"

#include <QSqlQueryModel>
#include <QCompleter>

FormVenta::FormVenta(QWidget* parent, Qt::WFlags fl ):
FormMovimiento(parent, fl, FormMovimiento::venta )
{
 // Verificar si las caravanas provienen del mismo establecimiento siempre
 // si es asi, verificar que no se coloquen caravanas que no existen en ese establecimiento
 // Creo el autocompletar con los datos
 connect( CBEstablecimientoOrigen, SIGNAL( indexChanged( int ) ), this, SLOT( filtrarPorEstablecimiento( int ) ) );
}


FormVenta::~FormVenta()
{
}

/*!
    \fn FormVenta::cerrar()
 */
void FormVenta::cerrar()
{
 close();
}


/*!
    \fn FormVenta::guardar()
 */
void FormVenta::guardar()
{
    /// @todo implement me
}


/*!
    \fn FormVenta::filtrarPorEstablecimiento( int idCombo )
 */
void FormVenta::filtrarPorEstablecimiento( int idCombo )
{
 // Busco el id del establecimiento del combo
 int id_establecimiento = CBEstablecimientoOrigen->model()->data( CBEstablecimientoOrigen->model()->index( idCombo, 0 ), Qt::UserRole ).toInt();
 LENumCar->setCompleter( 0 );
 if( completador == 0 )
 {
  completador = new QCompleter( LENumCar );
 }
 if( modelo == 0 )
 {
  modelo = new QSqlQueryModel( completador );
 }
 // Selecciono todos los tri que tuvieron movimientos hacia ese establecimiento
 // SELECT id_tri FROM car_tri WHERE id_estab_destino = '%1'
 // Despues busco todos las caravanas que estuvieron en esos tri
 // SELECT id_caravana FROM car_carav_tri WHERE id_tri IN (  )
 // Selecciono los codigos que se encuentran en los establecimientos
 modelo->setQuery( QString( "SELECT codigo FROM car_caravanas WHERE id_caravana IN ( SELECT id_caravana FROM car_carav_tri WHERE id_tri IN ( SELECT id_tri FROM car_tri WHERE id_estab_destino = '%1' ) )" ).arg( id_establecimiento ) );
 completador->setModel( modelo );
 LENumCar->setCompleter( completador );
}
