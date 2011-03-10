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
#include "productos.h"
#include "vproductos.h"
#include "vcategorias.h"
#include "preferencias.h"
#include <QSqlDatabase>

Q_EXPORT_PLUGIN2( productos, productos );


/*!
    \fn productos::accionesBarra()
 */
QList<QActionGroup *> productos::accionesBarra()
{
 QList<QActionGroup *> lista;
 QActionGroup *ventas = new QActionGroup( this );
 ventas->setObjectName( "ventas" );
 ventas->setProperty( "icono", ":/imagenes/ventas.jpg" );
 ventas->setProperty( "titulo", "Ventas" );
 ventas->addAction( ActProductos );
 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 { ventas->addAction( ActCategorias ); }
 lista.append( ventas );
 return lista;
}


/*!
    \fn productos::nombre() const
 */
QString productos::nombre() const
{
  return "productos";
}

#include "formprefproductos.h"
/*!
    \fn productos::formsPreferencias()
 */
QWidgetList productos::formsPreferencias()
{
 QWidgetList lista;
 lista.append( new FormPrefProductos() );
 return lista;
}


/*!
    \fn productos::inicializar()
 */
bool productos::inicializar()
{
 Q_INIT_RESOURCE(productos);
 _acciones.clear();

 ActProductos = new QAction( "Ver Productos", this );
 ActProductos->setIcon( QIcon( ":/imagenes/productos.png" ) );
 ActProductos->setStatusTip( "Ver la lista de todos los productos" );
 ActProductos->setToolTip( "Ver la lista de prodcutos" );
 connect( ActProductos, SIGNAL( triggered() ), this, SLOT( verProductos() ) );

 ////////////////////////////////
 // Muestra las categorias
 ////////////////////////////////
 ActCategorias = new QAction( "Categorias", this );
 ActCategorias->setStatusTip( "Muestra las categorias de productos que hay" );
 ActCategorias->setIcon( QIcon( ":/imagenes/categorias.jpg" ) );
 connect( ActCategorias, SIGNAL( triggered() ), this, SLOT( categorias() ) );

 _acciones.append( ActProductos );
 _acciones.append( ActCategorias );

 return true;
}


/*!
    \fn productos::verificarTablas()
 */
bool productos::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "producto" ) )
 { qWarning( "Productos::Error al buscar la tabla producto" ); return false; }
 else if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "categoria_producto" ) )
 { qWarning( "Productos::Error al buscar la tabla categoria_producto" ); return false; }
 return true;
}


/*!
    \fn productos::tipo() const
 */
int productos::tipo() const
{
 return EPlugin::comun;
}


/*!
    \fn productos::crearMenu( QMenuBar *m )
 */
void productos::crearMenu( QMenuBar *m )
{
 QMenu *menuHer = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHer == 0 )
 {
     qDebug( "Productos::Error en las baras de menu" );
 }
 else
 {
  menuHer->addAction( ActProductos );
  menuHer->addAction( ActCategorias );
 }
}


/*!
    \fn productos::version() const
        Devuelve la version del plugin
 */
double productos::version() const
{
 return 0.12;
}

/*!
    \fn productos::verProductos()
        Muestra la lista de productos
 */
void productos::verProductos()
{ emit agregarVentana( new VProductos( ) ); }


/*!
    \fn productos::crearToolBar( QToolBar *t )
 */
void productos::crearToolBar( QToolBar *t )
{
    (void)t;
 return;
}

/*!
    \fn productos::categorias()
        Muestra la ventana de categorias
 */
void productos::categorias()
{ emit agregarVentana( new VCategorias() ); }


/*!
    \fn productos::seCierraGestotux()
 */
void productos::seCierraGestotux()
{
 Q_CLEANUP_RESOURCE(productos);
 qDebug( "Productos::Cerrando" );
 return;
}
