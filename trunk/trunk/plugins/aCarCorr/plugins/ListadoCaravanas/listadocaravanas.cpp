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
#include "listadocaravanas.h"

Q_EXPORT_PLUGIN2( listadocaravanas, ListadoCaravanas );

/*!
    \fn ListadoCaravanas::inicializar()
 */
bool ListadoCaravanas::inicializar()
{
 ActInformeCaravanas = new QAction( this );
 ActInformeCaravanas->setText( "Caravanas x establecimiento" );
 connect( ActInformeCaravanas, SIGNAL( triggered() ), this, SLOT( informeCaravanas() ) );
 return true;
}


/*!
    \fn ListadoCaravanas::nombre() const
 */
QString ListadoCaravanas::nombre() const
{
 return "listadocaravanas";
}


/*!
    \fn ListadoCaravanas::version() const
 */
double ListadoCaravanas::version() const
{
 return 0.1;
}


/*!
    \fn ListadoCaravanas::crearMenu( QMenu *menu )
 */
void ListadoCaravanas::crearMenu( QMenu *menu )
{
  menu->addAction( ActInformeCaravanas );
}

