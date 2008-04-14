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
#include "informescategorizados.h"

QStackedWidget *InformesCategorizados::_formCen = 0;

QString InformesCategorizados::nombre() const
{
 return "informescategorizados";
}

bool InformesCategorizados::inicializar(QStackedWidget* form)
{
}

double InformesCategorizados::version() const
{
 return 0.1;
}

void InformesCategorizados::crearMenu(QMenu* m)
{
}

Q_EXPORT_PLUGIN2(informecategorizado, InformesCategorizados )


/*!
    \fn InformesCategorizados::impresionPersonalizada()
 */
bool InformesCategorizados::impresionPersonalizada() const
{
    /// @todo implement me
}


/*!
    \fn InformesCategorizados::imprimir()
 */
void InformesCategorizados::imprimir()
{
    /// @todo implement me
}
