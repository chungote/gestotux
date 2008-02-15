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
#include "actualizacion.h"
#include <QFtp>

QStackedWidget *actualizacion::_formCen = 0;
QSettings *actualizacion::_pref = 0;

Q_EXPORT_PLUGIN2(actualizar, actualizacion )

/*!
    \fn EActualizacion::detener()
 */
void actualizacion::detener()
{
  _continuar_actualizando = false;
}


/*!
    \fn EActualizacion::iniciar()
 */
void actualizacion::iniciar()
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
  /*preferencias *p = preferencias::getInstancia();
  QString host = p->value( "actualizaciones/host", "tranfuga.no-ip.org" ).toString();
  quint16 puerto = p->value( "actualizaciones/puerto", 21 ).toInt();
  ftp->connectToHost( host, puerto );
  ftp->cd( gestotux::plugin()->directorioActualizaciones() );*/
}



/*!
    \fn actualizacion::tipo()
 */
int actualizacion::tipo()
{
 return EPlugin::comun;
}


/*!
    \fn actualizacion::nombre()
 */
QString actualizacion::nombre()
{
 return "actualizar";
}

/*!
    \fn HiComp::accionesBarra()
 */
QList<QAction *> actualizacion::accionesBarra() const
{
 return _acciones;
}

/*!
    \fn actualizacion::inicializar( QStackedWidget *formCen, QSettings *pref )
 */
bool actualizacion::inicializar( QStackedWidget *formCen, QSettings *pref )
{
 _formCen = formCen;
 _pref = pref;
 return true;
}

QStackedWidget *actualizacion::tabs()
{
 return _formCen;
}

QSettings *actualizacion::pref()
{
 return _pref;
}


/*!
    \fn actualizacion::formsPreferencias()
 */
QWidgetList actualizacion::formsPreferencias()
{
    /// @todo implement me
}
