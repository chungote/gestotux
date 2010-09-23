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

#include "VCierresAnteriores.h"
#include "mmovimientoscaja.h"

VCierresAnteriores::VCierresAnteriores( QWidget *parent ) :
EVLista(parent)
{
    this->setObjectName( "ver_cierres_anteriores" );
    this->setWindowTitle( "Ver cierres anteriores");
    /*this->setWindowIcon( QIcon( ":/imagenes/" ) );*/

    modelo = new MMovimientosCaja( this, false );

}
