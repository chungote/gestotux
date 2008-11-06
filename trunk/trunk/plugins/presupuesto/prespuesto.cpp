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
#include "prespuesto.h"

#include <QSettings>
#include <QStackedWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QAction>
#include <QActionGroup>
#include <QMenuBar>
#include "formagregarpresupuesto.h"

/*!
    \fn prespuesto::accionesBarra() const
 */
QList<QActionGroup *> prespuesto::accionesBarra()
{
  QList<QActionGroup *> lista;
  QActionGroup *presupuestos = new QActionGroup( this );
  presupuestos->setObjectName( "presupuestos" );
  presupuestos->setProperty( "titulo", "Presupuestos" );
  presupuestos->setProperty( "icono",  ":/imagenes/resumenes.png" );
  presupuestos->addAction( ActNuevoPresu );
  presupuestos->addAction( ActPresuAnteriores );
  lista.append( presupuestos );
  return lista;
}


/*!
    \fn prespuesto::nombre() const
 */
QString prespuesto::nombre() const
{
  return "presupuesto";
}


/*!
    \fn prespuesto::formsPreferencias()
 */
QWidgetList prespuesto::formsPreferencias()
{
  return QWidgetList();
}


/*!
    \fn prespuesto::inicializar()
 */
bool prespuesto::inicializar()
{
 Q_INIT_RESOURCE(presupuesto);
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


/*!
    \fn prespuesto::tipo() const
 */
int prespuesto::tipo() const
{
  return EPlugin::comun;
}


/*!
    \fn prespuesto::crearMenu( QMenuBar *m )
 */
void prespuesto::crearMenu( QMenuBar *m )
{
 QMenu *menuHer = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHer == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  QMenu *menuRecibos = menuHer->addMenu( "Presupuestos2" );
  menuRecibos->addAction( ActNuevoPresu );
  menuRecibos->addAction( ActPresuAnteriores );
 }
}


/*!
    \fn prespuesto::version() const
 */
double prespuesto::version() const
{
  return 0.1;
}


/*!
    \fn prespuesto::verificarTablas()
 */
bool prespuesto::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "presupuestos" ) )
 { qWarning( "Error al buscar la tabla presupuestos" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "producto" ) )
 { qWarning( "Error al buscar la tabla cproducto" ); return false; }
 return true;
}


Q_EXPORT_PLUGIN2(presupuesto, prespuesto )


/*!
    \fn prespuesto::nuevoPresupuesto()
 */
void prespuesto::nuevoPresupuesto()
{ emit agregarVentana( new FormAgregarPresupuesto() ); }


#include "vpresupuesto.h"
/*!
    \fn prespuesto::verAnteriores()
 */
void prespuesto::verAnteriores()
{ emit agregarVentana( new VPresupuesto() ); }


/*!
    \fn prespuesto::crearToolBar( QToolBar *t )
 */
void prespuesto::crearToolBar( QToolBar *t )
{
 t->addActions( _acciones );
}
