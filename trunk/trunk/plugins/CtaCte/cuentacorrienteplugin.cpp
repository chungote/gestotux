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
#include "cuentacorrienteplugin.h"

#include <QSqlDatabase>
#include <QApplication>
#include "preferencias.h"

bool CuentaCorrientePlugin::inicializar()
{
 if( preferencias::getInstancia()->value( "Preferencias/CtaCte/habilitada", true ).toBool() )
 { QApplication::instance()->setProperty( "habilitada-ctacte", true ); }
 else
 { QApplication::instance()->setProperty( "habilitada-ctacte", false ); return true; }

 ActCuentasCorrientes = new QAction( this );
 ActCuentasCorrientes->setText( "Cuentas Corrientes" );
 ActCuentasCorrientes->setIcon( QIcon( ":/imagenes/ctacte.png" ) );
 ActCuentasCorrientes->setToolTip( "Muestra la lista de cuentas corrientes" );
 connect( ActCuentasCorrientes, SIGNAL( triggered() ), this, SLOT( verCuentasCorrientes() ) );

 return true;
}

bool CuentaCorrientePlugin::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "ctacte" ) )
 { qWarning( "Error al buscar la tabla de cuenta corriente" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "item_ctacte" ) )
  { qWarning( "Error al buscar la tabla de item cuenta corriente" ); return false; }
 return true;
}

double CuentaCorrientePlugin::version() const
{
 return 0.1;
}

int CuentaCorrientePlugin::tipo() const
{
 return EPlugin::comun;
}

QList< QActionGroup * > CuentaCorrientePlugin::accionesBarra()
{
 return QList<QActionGroup *>();
}

QString CuentaCorrientePlugin::nombre() const
{
 return "ctacte";
}

#include "formprefctacte.h"

QWidgetList CuentaCorrientePlugin::formsPreferencias()
{
 QWidgetList lista;
 lista.append( new FormPrefCtaCte() );
 return lista;
}

void CuentaCorrientePlugin::crearMenu( QMenuBar* m )
{
 QMenu *menuHerramientas = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHerramientas == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  menuHerramientas->addAction( ActCuentasCorrientes );
 }
}

void CuentaCorrientePlugin::crearToolBar(QToolBar* t)
{
}

void CuentaCorrientePlugin::seCierraGestotux()
{
 qDebug( "Cerrado plugin CtaCte" );
}

Q_EXPORT_PLUGIN2( ctacte, CuentaCorrientePlugin );

#include "vcuentacorriente.h"
/*!
    \fn CuentaCorrientePlugin::verCuentasCorrientes()
 */
void CuentaCorrientePlugin::verCuentasCorrientes()
{
 emit agregarVentana( new VCuentaCorriente() );
}
