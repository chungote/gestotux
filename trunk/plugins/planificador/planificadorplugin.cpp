/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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
#include "planificadorplugin.h"

#include "calendario.h"
//#include "vcalendario.h"
#include "QSqlDatabase"

bool PlanificadorPlugin::inicializar()
{
 Q_INIT_RESOURCE(planificador);

 ActCalendario = new QAction( this );
 ActCalendario->setText( "Ver Calendario" );
 ActCalendario->setShortcut( QKeySequence( "Ctrl + T" ) );
 ActCalendario->setStatusTip( "Visualizar el calendario ( Ctrl + T ) ");
 connect( ActCalendario, SIGNAL(triggered()), this, SLOT( verCalendario()));
 return true;
}

bool PlanificadorPlugin::verificarTablas()
{
    if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "calendarios" ) )
    { qWarning( "Error al buscar la tabla de calendarios" ); return false; }
    if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "citas" ) )
    { qWarning( "Error al buscar la tabla de citas" ); return false; }
    return true;
}

double PlanificadorPlugin::version() const
{
 return 0.01;
}

int PlanificadorPlugin::tipo() const
{
 return EPlugin::comun;
}

QList< QActionGroup * > PlanificadorPlugin::accionesBarra()
{
 return QList<QActionGroup*>();
}

QString PlanificadorPlugin::nombre() const
{
 return "planificador";
}

QWidgetList PlanificadorPlugin::formsPreferencias()
{
 return QWidgetList();
}

void PlanificadorPlugin::crearMenu(QMenuBar* m)
{
    QMenu *mPlanificador = m->addMenu( "Agenda" );
    mPlanificador->setObjectName( "menuPlanificador" );
    mPlanificador->addAction( ActCalendario );
}

void PlanificadorPlugin::crearToolBar(QToolBar* t)
{
}

void PlanificadorPlugin::verCalendario()
{
    VCalendario *v = new VCalendario();
    connect( v, SIGNAL( agregarDockWidget( Qt::DockWidgetArea, QDockWidget * ) ), this, SIGNAL( agregarDockWidget( Qt::DockWidgetArea, QDockWidget *) )  );
    agregarVentana( v );
}

void PlanificadorPlugin::seCierraGestotux()
{
  Q_CLEANUP_RESOURCE(planificador);
}

Q_EXPORT_PLUGIN2( planificador, PlanificadorPlugin );
