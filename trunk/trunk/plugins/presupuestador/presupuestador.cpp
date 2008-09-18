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
    \fn presupuestador::accionesBarra() const
 */
QList<QAction *> presupuestador::accionesBarra() const
{
 return _acciones;
}

bool presupuestador::inicializar( QSettings *pref )
{
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

 return verificarTablas();

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
    \fn presupuestador::nombre() const
 */
QString presupuestador::nombre() const
{
 return "presupuestador";
}


/*!
    \fn presupuestador::tipo() const
 */
int presupuestador::tipo() const
{
  return EPlugin::info;
}



/*!
    \fn presupuestador::verAnteriores()
 */
void presupuestador::verAnteriores()
{ emit agregarVentana( new FormPresupuestosAnteriores() ); }


/*!
    \fn presupuestador::nuevoPresupuesto()
 */
void presupuestador::nuevoPresupuesto()
{ emit agregarVentana( new FormNuevoPresupuesto() ); }


/*!
    \fn presupuestador::crearmenu( QMenuBar *m )
 */
void presupuestador::crearMenu( QMenuBar *m )
{
 QMenu *menuHer = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHer == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  QMenu *menuRecibos = menuHer->addMenu( "Presupuestos" );
  menuRecibos->addAction( ActNuevoPresu );
  menuRecibos->addAction( ActPresuAnteriores );
 }
}


/*!
    \fn presupuestador::verificarTablas()
 */
bool presupuestador::verificarTablas()
{
 return true;
}


/*!
    \fn presupuestador::version() const
 */
double presupuestador::version() const
{
  return 0.1;
}

QSettings *presupuestador::pref()
{
 return _pref;
}


/*!
    \fn presupuestador::empresa() const
 */
QString presupuestador::empresa() const
{
  return QString();
}


/*!
    \fn presupuestador::companeros()
 */
QString presupuestador::companeros()
{
 return QString();
}
