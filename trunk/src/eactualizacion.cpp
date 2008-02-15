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
#include "eactualizacion.h"
#include "preferencias.h"
#include "gestotux.h"
#include "einfoprogramainterface.h"
#include <QFtp>

EActualizacion::EActualizacion( QWidget *parent )
: EVentana ( parent ), Ui_FormActualizacionBase()
{
 setupUi( this );

 PBAccion->setIcon( QIcon( ":/imagenes/next.png" ) );
 connect( PBAccion, SIGNAL( clicked() ), this, SLOT( iniciar() ) );
}


EActualizacion::~EActualizacion()
{}




/*!
    \fn EActualizacion::detener()
 */
void EActualizacion::detener()
{
  _continuar_actualizando = false;
}


/*!
    \fn EActualizacion::iniciar()
 */
void EActualizacion::iniciar()
{
  _continuar_actualizando = true;
  PBAccion->setIcon( QIcon( ":/imagenes/stop.png" ) );
  PBAccion->setText( "Detener" );
  disconnect( PBAccion, SIGNAL( clicked() ), this, SLOT( iniciar() ) );
  connect( PBAccion, SIGNAL(clicked() ), this, SLOT( detener() ) );

  ftp = new QFtp( this );
  connect( ftp, SIGNAL( commandFinished( int, bool ) ), this, SLOT( finComando( int, bool ) ) );

  //Inicio la verificacion
  // Busco los datos desde el registro para el host y puerto
  preferencias *p = preferencias::getInstancia();
  QString host = p->value( "actualizaciones/host", "tranfuga.no-ip.org" ).toString();
  quint16 puerto = p->value( "actualizaciones/puerto", 21 ).toInt();
  ftp->connectToHost( host, puerto );
  ftp->cd( gestotux::plugin()->directorioActualizaciones() );
}
