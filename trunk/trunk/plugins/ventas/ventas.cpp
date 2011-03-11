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
#include "ventas.h"

#include <QSqlDatabase>

Q_EXPORT_PLUGIN2( ventas, Ventas );

/*!
    \fn Ventas::accionesBarra()
 */
QList<QActionGroup *> Ventas::accionesBarra()
{
 QList<QActionGroup *> lista;
 /////////////////////////////////////////////////////////////
 // Ventas
 QActionGroup *ventas = new QActionGroup( this );
 ventas->setObjectName( "ventas" );
 ventas->setProperty( "icono", ":/imagenes/ventas.jpg" );
 ventas->setProperty( "titulo", "Ventas" );
 ventas->addAction( ActAgregarVentas );
 lista.append( ventas );
 return lista;
}


/*!
    \fn Ventas::nombre() const
 */
QString Ventas::nombre() const
{
  return "ventas";
}

#include "formprefventa.h"
/*!
    \fn Ventas::formsPreferencias()
 */
QWidgetList Ventas::formsPreferencias()
{
    QWidgetList lista;
    lista.append( new FormPrefVenta() );
    return lista;
}


/*!
    \fn Ventas::inicializar()
 */
bool Ventas::inicializar()
{
 Q_INIT_RESOURCE(ventas);
 _acciones.clear();

 ActAgregarVentas = new QAction( "Agregar venta", this );
 ActAgregarVentas->setIcon( QIcon( ":/imagenes/factura-nueva.png" ) );
 connect( ActAgregarVentas, SIGNAL( triggered() ), this, SLOT( agregarVenta() ) );

 return true;
}


/*!
    \fn Ventas::verificarTablas()
 */
bool Ventas::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "producto" ) )
 { qWarning( "Ventas::Error al buscar la tabla producto" ); return false; }
 else if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "categoria_producto" ) )
 { qWarning( "Ventas::Error al buscar la tabla categorias_producto" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "ventas" ) )
 { qWarning( "Ventas::Error al buscar la tabla ventas" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "ventas_productos" ) )
 { qWarning( "Ventas::Error al buscar la tabla ventas_productos" ); return false; }
 return true;
}


/*!
    \fn Ventas::tipo() const
 */
int Ventas::tipo() const
{
 return EPlugin::comun;
}


/*!
    \fn Ventas::crearMenu( QMenuBar *m )
 */
void Ventas::crearMenu( QMenuBar *m )
{
 QMenu *mVentas = m->findChild<QMenu *>( "menuVentas" );
 if( mVentas == 0 )
 {
  mVentas = m->addMenu( "Ventas" );
  mVentas->setObjectName( "menuVentas" );
 }
 QList<QAction*> lista;
 lista.append( ActAgregarVentas );
 QAction *sep = new QAction( mVentas );
 sep->setSeparator( true );
 mVentas->insertActions( mVentas->actions().first(), lista );
}


/*!
    \fn Ventas::version() const
 */
double Ventas::version() const
{
 return 0.11;
}

void Ventas::crearToolBar( QToolBar *t )
{
    (void)t;
}


#include "formagregarventa.h"
/*!
    \fn Ventas::agregarVenta()
 */
void Ventas::agregarVenta()
{ emit agregarVentana( new FormAgregarVenta() ); }



/*!
    \fn Ventas::seCierraGestotux()
 */
void Ventas::seCierraGestotux()
{
 Q_CLEANUP_RESOURCE(ventas);
 qDebug( "Cerrado plugin ventas" );
 return;
}
