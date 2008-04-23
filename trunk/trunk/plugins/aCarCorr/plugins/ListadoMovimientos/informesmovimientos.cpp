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
#include "informesmovimientos.h"

#include <QAction>
#include <QMenu>
#include "formfiltro.h"
#include <QStackedWidget>
#include "erenderizadorinforme.h"
#include "einforme.h"

QStackedWidget *InformesMovimientos::_formCen = 0;

QString InformesMovimientos::nombre() const
{
 return "informesMovimientos";
}

bool InformesMovimientos::inicializar( QStackedWidget *form )
{
 _formCen = form;

 ActInformeFiltroTotal = new QAction( "Personalizado...", this );
 connect( ActInformeFiltroTotal, SIGNAL( triggered() ), this, SLOT( informeCompleto() ) );

 return true;
}

double InformesMovimientos::version() const
{
 return 0.1;
}

void InformesMovimientos::crearMenu(QMenu* m)
{
 m->addAction( ActInformeFiltroTotal );
}

Q_EXPORT_PLUGIN2(movimientos, InformesMovimientos );


/*!
    \fn InformesMovimientos::informeCompleto()
 */
void InformesMovimientos::informeCompleto()
{
 FormFiltro *f = new FormFiltro( _formCen );
 if( f->exec() == QDialog::Accepted )
 {
	// Genero un nuevo informe
	EInforme *fa = new EInforme( _formCen );
	_formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( fa ) ) );
	// Genero los contenidos del informe
	ERenderizadorInforme *render = new ERenderizadorInforme( this );
	render->setPropiedades( f );
	// lo muestro
	render->hacerInforme();
	fa->setDocument( render->documento() );
 }
}


/*!
    \fn InformesMovimientos::impresionPersonalizada()
 */
bool InformesMovimientos::impresionPersonalizada() const
{
    /// @todo implement me
}


/*!
    \fn InformesMovimientos::imprimir()
 */
void InformesMovimientos::imprimir()
{
    /// @todo implement me
}
