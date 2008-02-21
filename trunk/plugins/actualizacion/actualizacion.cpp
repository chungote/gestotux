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
#include "formactualizacion.h"

QStackedWidget *actualizacion::_formCen = 0;
QSettings *actualizacion::_pref = 0;

Q_EXPORT_PLUGIN2(actualizar, actualizacion )

/*!
    \fn actualizacion::tipo()
 */
int actualizacion::tipo() const
{
 return EPlugin::comun;
}


/*!
    \fn actualizacion::nombre()
 */
QString actualizacion::nombre() const
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
 _acciones.clear();

 ActActualizar = new QAction( "Actualizar", this );
 ActActualizar->setIcon( QIcon( ":/imagenes/actualizar.png" ) );
 ActActualizar->setStatusTip( "Actualiza la aplicacion " );
 connect( ActActualizar, SIGNAL( triggered() ), this, SLOT( verForm() ) );
 
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
  return QWidgetList();
}


/*!
    \fn actualizacion::verForm()
 */
void actualizacion::verForm()
{
 FormActualizacion *f = new FormActualizacion( tabs() );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


/*!
    \fn actualizacion::crearMenu( QMenuBar *m )
 */
void actualizacion::crearMenu( QMenuBar *m )
{
 QMenu *menu = m->findChild<QMenu *>( "menuArchivo" );
 if( menu == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 { 
  menu->addAction( ActActualizar );
 }
}

void actualizacion::verificarTablas()
{}
