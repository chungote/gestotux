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
#include "formulariocentral.h"

#include "gestotux.h"
#include <QToolBar>
#include <QPushButton>

FormularioCentral::FormularioCentral( QWidget *parent )
: QTabWidget( parent )
{
 connect( this, SIGNAL( currentChanged( int ) ), this, SLOT( cambioWidget( int ) ) );
 PBCerrar = new QPushButton( this );
 PBCerrar->setFlat( true );
 PBCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 this->setCornerWidget( PBCerrar );
 connect( PBCerrar, SIGNAL( clicked() ), this, SLOT( cerrarActivo() ) );
}


FormularioCentral::~FormularioCentral()
{
}


void FormularioCentral::cambioWidget( int id )
{
 gestotux::barraAcciones()->clear();
 if( id > -1 )
 {
  gestotux::barraAcciones()->addActions( this->widget( id )->actions() );
 }
}


void FormularioCentral::cerrarActivo()
{
 removeTab( currentIndex() );
 cambioWidget( currentIndex() );
}


/*!
    \fn FormularioCentral::agregarForm( QWidget *ventana )
 */
void FormularioCentral::agregarForm( QWidget *ventana )
{
 if( ventana->objectName().isEmpty() )
 {
  qWarning( "intentando agregar ventana sin nombre, no aparecera" );
  return;
 }
 if( !existeVentana( ventana->objectName() ) )
 {
  connect( ventana, SIGNAL( agregarVentana( QWidget * ) ), this, SLOT( agregarForm( QWidget * ) ) );
  this->setCurrentIndex( this->addTab( ventana, ventana->windowIcon(), ventana->windowTitle() ) );
  this->currentWidget()->setFocus( Qt::ActiveWindowFocusReason );
 }
 else
 {
   // Busco el form que tiene la ventana y lo pongo como actual
   //qWarning( qPrintable( "Ya existe la ventana " + ventana->objectName() ) );
   this->setCurrentWidget( this->findChild<QWidget *>( ventana->objectName() ) );
   ventana->deleteLater();
 }
}


/*!
    \fn FormularioCentral::existeVentana( QString nombre )
 */
bool FormularioCentral::existeVentana( QString nombre )
{
 if( this->findChild<QWidget *>( nombre ) == 0 )
 { return false; }
 else
 { return true; }
}
