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
#include "preferencias.h"

#include "formprefctacte.h"

FormPrefCtaCte::FormPrefCtaCte ( QWidget* parent, Qt::WFlags fl )
: QWidget ( parent, fl ), Ui::FormPrefCtaCteBase()
{
	setupUi ( this );
	this->setWindowTitle( "Cuenta Corriente" );
}

FormPrefCtaCte::~FormPrefCtaCte()
{
}

/*!
    \fn FormPrefCtaCte::guardar()
 */
void FormPrefCtaCte::guardar()
{
 preferencias::getInstancia()->setValue( "Preferencias/CtaCte/habilitada", GBHabilitar->isChecked() );
}


/*!
    \fn FormPrefCtaCte::aplicar()
 */
void FormPrefCtaCte::aplicar()
{
    /// \todo implement me
}


/*!
    \fn FormPrefCtaCte::cargar()
 */
void FormPrefCtaCte::cargar()
{
 GBHabilitar->setChecked( preferencias::getInstancia()->value( "Preferencias/CtaCte/habilitada", false ).toBool() );
}
