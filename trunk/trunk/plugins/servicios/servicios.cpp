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
#include "servicios.h"
#include <QSqlDatabase>

#include "vservicios.h"

bool Servicios::inicializar()
{
 Q_INIT_RESOURCE(servicios);

 //Acciones
 ActServicios = new QAction( this );
 ActServicios->setText( "Servicios" );
 ActServicios->setStatusTip( "Muestra todos los servicios disponibles que hay" );
 connect( ActServicios, SIGNAL( triggered() ), this, SLOT( mostrarServicios() ) );
 return true;
}

bool Servicios::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "servicios" ) )
 { qWarning( "Error al buscar la tabla de servicios" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "servicios_cliente" ) )
 { qWarning( "Error al buscar la tabla de servicios_cliente" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "recargos" ) )
 { qWarning( "Error al buscar la tabla de recargos" ); return false; }
 return true;
}

double Servicios::version() const
{
 return 0.1;
}

int Servicios::tipo() const
{
 return EPlugin::comun;
}

QList< QActionGroup * > Servicios::accionesBarra()
{
 return QList<QActionGroup *>();
}

QString Servicios::nombre() const
{
 return "servicios";
}

QWidgetList Servicios::formsPreferencias()
{
 return QWidgetList();
}

void Servicios::crearMenu(QMenuBar* m)
{
 QMenu *serv = m->addMenu( "Servicios" );
 serv->addAction( ActServicios );
 return;
}

void Servicios::crearToolBar(QToolBar* t)
{
}

void Servicios::seCierraGestotux()
{
 Q_CLEANUP_RESOURCE(servicios);
}

/*!
    \fn Servicios::mostrarServicios
 */
void Servicios::mostrarServicios()
{
  emit agregarVentana( new VServicios() );
}

Q_EXPORT_PLUGIN2( servicios, Servicios );