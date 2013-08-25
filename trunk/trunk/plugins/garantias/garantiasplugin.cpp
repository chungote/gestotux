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
#include "garantiasplugin.h"

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
#include <QDebug>

/*!
    \fn GarantiasPlugin::accionesBarra()
        Retorna las acciones que tiene la barra lateral para este plugin
        @return Lista de acciones
 */
QList<QActionGroup *> GarantiasPlugin::accionesBarra()
{ return QList<QActionGroup*>(); }


bool GarantiasPlugin::inicializar()
{
 Q_INIT_RESOURCE(garantias);
 return true;
}

/*!
    \fn GarantiasPlugin::formsPreferencias()
 */
QWidgetList GarantiasPlugin::formsPreferencias()
{
 QWidgetList lista;
 return lista;
}

/*!
    \fn GarantiasPlugin::nombre() const
 */
QString GarantiasPlugin::nombre() const
{ return "garantias"; }


/*!
    \fn GarantiasPlugin::tipo() const
 */
int GarantiasPlugin::tipo() const
{ return EPlugin::comun; }


/*!
    \fn GarantiasPlugin::crearMenu( QMenuBar *m )
 */
void GarantiasPlugin::crearMenu( QMenuBar *m )
{
 /*QMenu *menuHer = m->findChild<QMenu *>( "menuArchivo" );
 menuHer->addSeparator();
 menuHer->addAction( ActBackup );*/
}

bool GarantiasPlugin::verificarTablas( QStringList )
{
 if( !QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).tables( QSql::Tables ).contains( "garantias" ) )
 { qWarning() << "Error al buscar la tabla garantias"; return false; }
 return true;
}


/*!
    \fn GarantiasPlugin::version() const
 */
double GarantiasPlugin::version() const
{  return 0.1; }

/*!
    \fn GarantiasPlugin::crearToolBar( QToolBar *t )
 */
void GarantiasPlugin::crearToolBar( QToolBar */*t*/ )
{}


/*!
    \fn GarantiasPlugin::seCierraGestotux()
 */
void GarantiasPlugin::seCierraGestotux()
{
 Q_CLEANUP_RESOURCE(garantias);
}

QAction *GarantiasPlugin::botonPantallaInicial()
{
    return ( new QAction( this ) );
}

Q_EXPORT_PLUGIN2( garantias, GarantiasPlugin )
