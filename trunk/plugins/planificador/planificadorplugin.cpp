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
    /*mPlanificador->addAction( ActAgregarCompra );
    mPlanificador->addSeparator();
    mPlanificador->addAction( ActCompras );*/
}

void PlanificadorPlugin::crearToolBar(QToolBar* t)
{
}

void PlanificadorPlugin::seCierraGestotux()
{
  Q_CLEANUP_RESOURCE(planificador);
}

Q_EXPORT_PLUGIN2( planificador, PlanificadorPlugin );

void PlanificadorPlugin::verCalendario()
{
 agregarVentana( new VCalendario() );
}
