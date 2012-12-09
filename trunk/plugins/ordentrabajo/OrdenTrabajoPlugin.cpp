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
#include "OrdenTrabajoPlugin.h"

#include <QSqlDatabase>

bool OrdenTrabajoPlugin::inicializar()
{
 Q_INIT_RESOURCE(ordentrabajo);
 ///////////////////////////////
 // Muestra las ordenes de trabajo
 //////////////////////////////
 ActOrdenTrabajo = new QAction( "Ordenes de trabajo", this );
 ActOrdenTrabajo->setStatusTip( "Muestra la lista de ordenes de trabajo" );
 ActOrdenTrabajo->setIcon( QIcon( ":/imagenes/orden_trabajo.png" ) );
 connect( ActOrdenTrabajo, SIGNAL( triggered() ), this, SLOT( verOrdenesTrabajo() ) );
 ///////////////////////////////////
 // Agrega una nueva orden de trabajo
 ///////////////////////////////////
 ActAgregarOrdenTrabajo = new QAction( "Agregar orden de trabajo", this );
 ActAgregarOrdenTrabajo->setStatusTip( "Agrega una nueva orden de trabajo" );
 //ActAgregarOrdenTrabajo->setIcon( QIcon( ":/imagenes/proveedores.jpg" ) );
 connect( ActAgregarOrdenTrabajo, SIGNAL( triggered() ), this, SLOT( agregarOrdenTrabajo() ) );
 ///////////////////////////////////
 // Muestra el listado de tecnicos
 ///////////////////////////////////
 ActVerTecnicos = new QAction( "Tecnicos", this );
 ActVerTecnicos->setStatusTip( "Muestra el listado de tecnicos habilitados" );
 ActVerTecnicos->setIcon( QIcon( ":/imagenes/tecnico.png" ) );
 connect( ActVerTecnicos, SIGNAL( triggered() ), this, SLOT( verTecnicos() ) );
 ///////////////////////////////////
 // Muestra los tipos de operaciones
 ///////////////////////////////////
 ActVerTipoOperacion = new QAction( "Tipo operaciones", this );
 ActVerTipoOperacion->setStatusTip( "Muestra el listado de operaciones disponibles" );
 //ActVerTipoOperacion->setIcon( QIcon( ":/imagenes/proveedores.jpg" ) );
 connect( ActVerTipoOperacion, SIGNAL( triggered() ), this, SLOT( verTipoOperacion() ) );

 return true;
}

bool OrdenTrabajoPlugin::verificarTablas( QStringList tablas )
{
 if( !tablas.contains( "orden_trabajo" ) )
 { qWarning( "OrdenTrabajoPlugin::Error al buscar la tabla orden_trabajo" ); return false; }
 if( !tablas.contains( "tecnico" ) )
 { qWarning( "OrdenTrabajoPlugin::Error al buscar la tabla tecnico" ); return false; }
 if( !tablas.contains( "equipamiento" ) )
 { qWarning( "OrdenTrabajoPlugin::Error al buscar la tabla equipamiento" ); return false; }
 if( !tablas.contains( "tipo_operacion_orden_trabajo" ) )
 { qWarning( "OrdenTrabajoPlugin::Error al buscar la tabla tipo_operacion_orden_trabajo" ); return false; }
 if( !tablas.contains( "operacion_orden_trabajo" ) )
 { qWarning( "OrdenTrabajoPlugin::Error al buscar la tabla operacion_orden_trabajo" ); return false; }
 return true;
}

double OrdenTrabajoPlugin::version() const
{ return 0.1; }

int OrdenTrabajoPlugin::tipo() const
{ return EPlugin::comun; }

QList< QActionGroup * > OrdenTrabajoPlugin::accionesBarra()
{
 /*QList<QActionGroup *> lista;
 QActionGroup *compras = new QActionGroup( this );
 compras->setObjectName( "compras" );
 compras->addAction( ActProveedores );
 lista.append( compras );
 return lista;*/
 return QList<QActionGroup *>();
}

QString OrdenTrabajoPlugin::nombre() const
{ return "ordentrabajo"; }

QWidgetList OrdenTrabajoPlugin::formsPreferencias()
{ return QWidgetList(); }

void OrdenTrabajoPlugin::crearMenu( QMenuBar* m )
{
 QMenu *menuHerramientas = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHerramientas != 0 ) {
     QMenu *menuOrden = menuHerramientas->addMenu( "Orden de trabajo" );
     menuOrden->addAction( ActAgregarOrdenTrabajo );
     menuOrden->addAction( ActOrdenTrabajo );
     menuOrden->addAction( ActVerTecnicos );
     menuOrden->addAction( ActVerTipoOperacion );
 }
}

void OrdenTrabajoPlugin::crearToolBar(QToolBar* /*t*/)
{}

QAction *OrdenTrabajoPlugin::botonPantallaInicial()
{ return ActOrdenTrabajo; }

/*!
    \fn OrdenTrabajoPlugin::seCierraGestotux()
 */
void OrdenTrabajoPlugin::seCierraGestotux()
{ Q_CLEANUP_RESOURCE(ordentrabajo); return; }

void OrdenTrabajoPlugin::verOrdenesTrabajo() {}
void OrdenTrabajoPlugin::agregarOrdenTrabajo() {}
void OrdenTrabajoPlugin::verTipoOperacion() {}

#include "vtecnicos.h"
void OrdenTrabajoPlugin::verTecnicos()
{
    emit agregarVentana( new VTecnicos() );
}

Q_EXPORT_PLUGIN2( ordentrabajo, OrdenTrabajoPlugin )

