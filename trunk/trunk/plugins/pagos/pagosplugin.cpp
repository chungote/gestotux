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
#include <QAction>
#include <QSqlDatabase>
#include "pagosplugin.h"


bool PagosPlugin::inicializar()
{
 Q_INIT_RESOURCE(pagos);
 ActPagos = new QAction( "Pagos", this );
 ActPagos->setStatusTip( "Visualiza todos los pagos echos recientemente" );
 ActPagos->setIcon( QIcon( ":/imagenes/recibo.png" ) );
 connect( ActPagos, SIGNAL( triggered() ), this, SLOT( verPagos() ) );

 ActAgregarRecibo = new QAction( "Agregar Recibo", this );
 ActAgregarRecibo->setIcon( QIcon( ":/imagenes/recibo-nuevo.png" ) );
 ActAgregarRecibo->setStatusTip( "Ingresa un nuevo registro de recibo al sistema y lo imprime automaticamente" );
 connect( ActAgregarRecibo, SIGNAL( triggered() ), this, SLOT( agregarRecibo() ) );

 return true;
}

bool PagosPlugin::verificarTablas( QStringList tablas )
{
 if( !tablas.contains( "recibos" ) )
 { qWarning( "Recibos::Error al buscar la tabla recibos" ); return false; }
 return true;
}

double PagosPlugin::version() const
{
 return 0.1;
}

int PagosPlugin::tipo() const
{
 return EPlugin::comun;
}

QList< QActionGroup * > PagosPlugin::accionesBarra()
{
 return QList<QActionGroup*>();
}

QString PagosPlugin::nombre() const
{
 return "pagos";
}

QWidgetList PagosPlugin::formsPreferencias()
{
 return QWidgetList();
}

void PagosPlugin::crearMenu( QMenuBar* m )
{
 QMenu *mVentas = m->findChild<QMenu *>( "menuVentas" );
 if( mVentas == 0 )
 {
  mVentas = m->addMenu( "Ventas" );
  mVentas->setObjectName( "menuVentas" );
 }
 mVentas->addAction( ActPagos );
 mVentas->addAction( ActAgregarRecibo );
}

void PagosPlugin::crearToolBar(QToolBar* t)
{
    (void)t;
}

void PagosPlugin::seCierraGestotux()
{
    Q_CLEANUP_RESOURCE(pagos);
}

#include "vpagos.h"
/*!
    \fn PagosPlugin::verPagos()
 */
void PagosPlugin::verPagos()
{
 emit agregarVentana( new VPagos() );
}

#include "formagregarrecibo.h"
/*!
    \fn PagosPlugin::agregarRecibo()
*/
void PagosPlugin::agregarRecibo()
{
    emit agregarVentana( new FormAgregarRecibo() );
}

Q_EXPORT_PLUGIN2( pagos, PagosPlugin );