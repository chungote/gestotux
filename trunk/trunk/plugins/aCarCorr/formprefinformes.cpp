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
#include "formprefinformes.h"
#include "einformeimpresora.h"
#include "preferencias.h"
#include <QIcon>

FormPrefInformes::FormPrefInformes(QWidget *parent)
 : QPageSetupDialog( new EInformeImpresora(), parent )
{
 this->setWindowTitle( "Informes" );
 this->setWindowIcon( QIcon( ":/imagenes/impresora.png" ) );
}


FormPrefInformes::~FormPrefInformes()
{
}


void FormPrefInformes::cargar()
{
 // El fomulario ya esta cargado
}

void FormPrefInformes::aplicar()
{
 // no hago nada
}

void FormPrefInformes::guardar()
{
 qWarning( "Echo" );
 static_cast<EInformeImpresora *>(this->printer())->guardar();
}


/*!
    \fn FormPrefInformes::accept()
 */
void FormPrefInformes::accept()
{
 guardar();
}


/*!
    \fn FormPrefInformes::done( int r )
 */
void FormPrefInformes::done( int r )
{
 qWarning( "Echo" );
}


/*!
    \fn FormPrefInformes::reject()
 */
void FormPrefInformes::reject()
{
 // no hago nada para que no se cierre el dialogo
}
