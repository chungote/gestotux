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
#include "presupuestador.h"
#include "formmodificarpresupuesto.h"
#include "formnuevopresupuesto.h"
#include "formpresupuestosanteriores.h"

#include <QMenuBar>

QStackedWidget *presupuestador::_formCen = 0;
QSettings *presupuestador::_pref = 0;

QString presupuestador::nombrePrograma()  const
{
 return "Presupuestador - 0.1";
}

Q_EXPORT_PLUGIN2(presupuestador, presupuestador )

QIcon presupuestador::iconoPrograma() const
{
 return QIcon( ":/imagenes/icono.png" );
}

/*!
    \fn presupuestador::accionesBarra()
 */
QList<QAction *> presupuestador::accionesBarra() const
{
 return _acciones;
}

bool presupuestador::inicializar( QStackedWidget *formCen, QSettings *pref )
{
 _formCen = formCen;
 _pref = pref;
 _acciones.clear();
 // Genero las acciones y la lista
 ActNuevoPresu = new QAction( "Nuevo Prespuesto", this );
 ActNuevoPresu->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
 ActNuevoPresu->setStatusTip( "Genera un nuevo presupuesto" );
 connect( ActNuevoPresu, SIGNAL( triggered() ), this, SLOT( nuevoPresupuesto() ) );
 
 ActPresuAnteriores = new QAction( "Presupuestos Anteriores", this );
 ActPresuAnteriores->setIcon( QIcon( ":/imagenes/anteriores.png" ) );
 ActPresuAnteriores->setStatusTip( "Ver los presupuestos anteriores" );
 connect( ActPresuAnteriores, SIGNAL( triggered() ), this, SLOT( verAnteriores() ) );

 _acciones.append( ActNuevoPresu );
 _acciones.append( ActPresuAnteriores );
 
 return true;

}


QStackedWidget *presupuestador::tabs()
{
 return _formCen;
}

QSettings *presupuestador::pref()
{
 return _pref;
}

QString presupuestador::directorioBackup() const
{
  return "presupuestador";
}


QString presupuestador::directorioActualizaciones() const
{
 return "presupuestador";
}


/*!
    \fn presupuestador::formsPreferencias()
 */
QWidgetList presupuestador::formsPreferencias()
{
 return QWidgetList();
}


/*!
    \fn presupuestador::nombre()
 */
QString presupuestador::nombre()
{
 return "presupuestador";
}


/*!
    \fn presupuestador::tipo()
 */
int presupuestador::tipo()
{
  return EPlugin::info;
}



/*!
    \fn presupuestador::verAnteriores()
 */
void presupuestador::verAnteriores()
{
 FormPresupuestosAnteriores *f = new FormPresupuestosAnteriores( tabs() );
_formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


/*!
    \fn presupuestador::nuevoPresupuesto()
 */
void presupuestador::nuevoPresupuesto()
{
 FormNuevoPresupuesto *f = new FormNuevoPresupuesto( tabs() );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


/*!
    \fn presupuestador::crearmenu( QMenu *m )
 */
void presupuestador::crearMenu( QMenu *m )
{
    /// @todo implement me
}
