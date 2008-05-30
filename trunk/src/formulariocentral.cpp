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

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QPrinter>
#include <QFileDialog>
#include "gestotux.h"
#include <QToolBar>
#include <QPushButton>
#include <QPrintDialog>
#include "preferencias.h"

FormularioCentral::FormularioCentral( QWidget *parent )
 : QStackedWidget( parent )
{
 connect( this, SIGNAL( currentChanged( int ) ), this, SLOT( cambioWidget( int ) ) );
}


FormularioCentral::~FormularioCentral()
{
}


void FormularioCentral::cambioWidget( int id )
{
//  qDebug( QString( "id nuevo: %1" ).arg( id ).toLocal8Bit() );
 if( id > -1 )
 {
  gestotux::barraAcciones()->clear();
  gestotux::barraAcciones()->addActions( this->widget( id )->actions() );
 }
}


void FormularioCentral::cerrarActivo()
{
 removeWidget( this->widget( currentIndex() ) );
 cambioWidget( currentIndex() );
}


/*!
    \fn FormularioCentral::agregarForm( QWidget *ventana )
 */
void FormularioCentral::agregarForm( QWidget *ventana )
{
 connect( ventana, SIGNAL( agregarVentana( QWidget * ) ), this, SLOT( agregarForm( QWidget * ) ) );
 this->setCurrentIndex( this->addWidget( ventana ) );
}
