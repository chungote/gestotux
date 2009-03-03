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
#include <QSqlDatabase>

QString presupuestador::nombrePrograma()  const
{
 return "Presupuestador - 0.1";
}


QIcon presupuestador::iconoPrograma() const
{
 return QIcon( ":/imagenes/icono.png" );
}

bool presupuestador::inicializar()
{
 // Genero las acciones y la lista
 ActNuevoPresu = new QAction( "Nuevo Prespuesto", this );
 ActNuevoPresu->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
 ActNuevoPresu->setStatusTip( "Genera un nuevo presupuesto" );
 connect( ActNuevoPresu, SIGNAL( triggered() ), this, SLOT( nuevoPresupuesto() ) );

 ActPresuAnteriores = new QAction( "Presupuestos Anteriores", this );
 ActPresuAnteriores->setIcon( QIcon( ":/imagenes/anteriores.png" ) );
 ActPresuAnteriores->setStatusTip( "Ver los presupuestos anteriores" );
 connect( ActPresuAnteriores, SIGNAL( triggered() ), this, SLOT( verAnteriores() ) );

 ActAutos = new QAction( "Automoviles", this );
 ActAutos->setIcon( QIcon( ":/imagenes/auto.png" ) );
 ActAutos->setStatusTip( "Listado de automobiles que se encuentran en el sistema" );
 connect( ActAutos, SIGNAL( triggered() ), this, SLOT( verAutos() ) );

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
  menuHer->addAction( ActAutos );
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
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "autos" ) )
 { qWarning( "Error al buscar la tabla de automoviles" ); return false; }
 return true;
}


/*!
    \fn presupuestador::version() const
 */
double presupuestador::version() const
{
  return 0.1;
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


Q_EXPORT_PLUGIN2(presupuestador, presupuestador )


/*!
    \fn presupuestador::publicidad()
 */
bool presupuestador::publicidad()
{ return false; }


/*!
    \fn presupuestador::accionesBarra()
 */
QList<QActionGroup *> presupuestador::accionesBarra()
{
  return QList<QActionGroup *>();
}


/*!
    \fn presupuestador::crearToolBar( QToolBar *t )
 */
void presupuestador::crearToolBar( QToolBar *t )
{
    /// @todo implement me
}


#include "vautos.h"

/*!
    \fn presupuestador::verAutos()
 */
void presupuestador::verAutos()
{
 emit agregarVentana( new VAutos() );
}
