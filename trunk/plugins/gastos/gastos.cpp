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
#include "gastos.h"
#include <QSqlDatabase>

Q_EXPORT_PLUGIN2( gastos, Gastos );

bool Gastos::inicializar()
{
 Q_INIT_RESOURCE(gastos);
 /////////////////////////////////////
 // Muestra los gastos
 /////////////////////////////////////
 ActGastos = new QAction( "Gastos", this );
 ActGastos->setStatusTip( "Ver la lista de gastos" );
 ActGastos->setIcon( QIcon( ":/imagenes/gasto.jpg" ) );
 connect( ActGastos, SIGNAL( triggered() ), this, SLOT( ver_gastos() ) );
 /////////////////////////////////////
 // Muestra el agregar un gasto
 /////////////////////////////////////
 ActAgregarGasto = new QAction( "Agregar Gasto", this );
 ActAgregarGasto->setStatusTip( "Agregar nuevo gasto" );
 ActAgregarGasto->setIcon( QIcon( ":/imagenes/gasto.jpg" ) );
 connect( ActAgregarGasto, SIGNAL( triggered() ), this, SLOT( agregarGasto() ) );

 return true;
}

bool Gastos::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "gastos" ) )
 { qWarning( "Error al buscar la tabla gastos" );	return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "categoria" ) )
 { qWarning( "Error al buscar la tabla categorias" );	return false; }
 return true;
}

double Gastos::version() const
{
 return 0.1;
}

int Gastos::tipo() const
{
 return EPlugin::comun;
}

QList< QActionGroup * > Gastos::accionesBarra()
{
 QList<QActionGroup *> lista;
 QActionGroup *compras = new QActionGroup( this );
 compras->setObjectName( "compras" );
 compras->addAction( ActAgregarGasto );
 lista.append( compras );
 return lista;
}

QString Gastos::nombre() const
{
 return "gastos";
}

QWidgetList Gastos::formsPreferencias()
{
 return QWidgetList();
}

void Gastos::crearMenu(QMenuBar* m)
{
 QMenu *menuHerramientas = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHerramientas == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  menuHerramientas->addAction( ActGastos );
 }
}

void Gastos::crearToolBar(QToolBar* t)
{}

#include "formagregargasto.h"
/*!
    \fn Gastos::agregarGasto()
	Abre la ventana para agregar un gasto
 */
void Gastos::agregarGasto()
{ emit agregarVentana( new FormAgregarGasto() ); }

#include "vgastos.h"
/*!
    \fn Gastos::ver_gastos()
 */
void Gastos::ver_gastos()
{ emit agregarVentana( new VGastos() ); }



/*!
    \fn Gastos::seCierraGestotux()
 */
void Gastos::seCierraGestotux()
{
 Q_CLEANUP_RESOURCE(gastos);
 qDebug( "Cerrado plugin gastos" );
 return;
}
