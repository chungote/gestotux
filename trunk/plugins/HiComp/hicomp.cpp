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
#include "hicomp.h"
#include "vrecibos.h"
#include "fprefrecibos.h"
#include "formagregarrecibo.h"

#include <QString>
#include <QIcon>
#include <QAction>
#include <QMenuBar>
#include <QList>
#include <QStackedWidget>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

QSettings *HiComp::_pref = 0;

QString HiComp::nombrePrograma()  const
{
 return "HiComp Computacion - 0.1";
}

Q_EXPORT_PLUGIN2(hicomp, HiComp )

QIcon HiComp::iconoPrograma() const
{
 return QIcon( ":/imagenes/icono.png" );
}

/*!
    \fn HiComp::accionesBarra()
 */
QList<QAction *> HiComp::accionesBarra() const
{
 return _acciones;
}


bool HiComp::inicializar( QSettings *pref  )
{
 _pref = pref;
 _acciones.clear();
 // Genero las acciones y la lista
 ActRecibos = new QAction( "Ver Recibos", this );
 ActRecibos->setToolTip( "Ver los recibos emitidos" );
 ActRecibos->setIcon( QIcon( ":/imagenes/anteriores.png" ) );
 connect( ActRecibos, SIGNAL( triggered() ), this, SLOT( verRecibosAnteriores() ) );

 ActNuevoRecibo = new QAction( "Nuevo Recibo", this );
 ActNuevoRecibo->setToolTip( "Crear un nuevo recibo" );
 ActNuevoRecibo->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
 connect( ActNuevoRecibo, SIGNAL( triggered() ), this, SLOT( nuevoRecibo() ) );

 _acciones.append( ActNuevoRecibo );

 return verificarTablas();
}


void HiComp::verRecibosAnteriores()
{ emit agregarVentana( new VRecibos() ); }


QSettings *HiComp::pref()
{
 return _pref;
}

QString HiComp::directorioBackup() const
{
  return "HiComp";
}


QString HiComp::directorioActualizaciones() const
{
 return "HiComp";
}


/*!
    \fn HiComp::formsPreferencias()
 */
QWidgetList HiComp::formsPreferencias()
{
 QWidgetList lista;
 lista.append( new FPrefRecibos() );
 return lista;
}


/*!
    \fn HiComp::nuevoRecibo()
 */
void HiComp::nuevoRecibo()
{ emit agregarVentana( new FormAgregarRecibo() ); }


/*!
    \fn HiComp::nombre()
 */
QString HiComp::nombre() const
{
 return "hicomp";
}


/*!
    \fn HiComp::tipo()
 */
int HiComp::tipo() const
{
  return EPlugin::info;
}


/*!
    \fn HiComp::crearMenu( QMenuBar *m )
 */
void HiComp::crearMenu( QMenuBar *m )
{
 QMenu *menuHer = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHer == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  QMenu *menuRecibos = menuHer->addMenu( "Recibos" );
  menuRecibos->addAction( ActRecibos );
  menuRecibos->addAction( ActNuevoRecibo );
 }
}

bool HiComp::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "recibos" ) )
 {qWarning( "Error al buscar las tablas del plugin hi comp - recibos" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "producto" ) )
 {qWarning( "Error al buscar las tablas del plugin hi comp - producto " ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "clientes" ) )
 {qWarning( "Error al buscar las tablas del plugin hi comp - clientes" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "categoria" ) )
 {qWarning( "Error al buscar las tablas del plugin hi comp - categoria" ); return false; }
 return true;
}


/*!
    \fn HiComp::version()
 */
double HiComp::version() const
{
  return 0.1;
}


/*!
    \fn HiComp::empresa() const
 */
QString HiComp::empresa() const
{
 return "HiComp Computacion";
}


/*!
    \fn HiComp::companeros()
 */
QString HiComp::companeros()
{
 return QString();
}
