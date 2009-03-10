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
#include "emautos.h"

EMAutos::EMAutos(QObject *parent)
 : QSqlQueryModel(parent)
{
 filtrarPorCliente( -1 );
}


EMAutos::~EMAutos()
{
}




/*!
    \fn EMAutos::filtrarPorCliente( id Cliente )
 */
void EMAutos::filtrarPorCliente( int id_cliente )
{
 if( id_cliente != -1 )
 {
  this->setQuery( QString( "SELECT patente, CONCAT(CONCAT(CONCAT(CONCAT(CONCAT(CONCAT( patente, ' - ' ) , marca ), ' ' ), modelo ), ' - ' ), color )  FROM autos WHERE id_cliente = %1" ).arg( id_cliente ) );
 }
 else
 {
  this->setQuery( "SELECT patente, CONCAT(CONCAT(CONCAT(CONCAT(CONCAT(CONCAT( patente, ' - ' ) , marca ), ' ' ), modelo ), ' - ' ), color )  FROM autos" );
 }
}
