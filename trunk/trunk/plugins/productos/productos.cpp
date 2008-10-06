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
#include <QSqlDatabase>

QSettings *productos::_pref = 0;

Q_EXPORT_PLUGIN2( productos, productos );


/*!
    \fn productos::accionesBarra() const
 */
QList<QActionGroup *> productos::accionesBarra()
{
 return QList<QActionGroup*>();
}


/*!
    \fn productos::nombre() const
 */
QString productos::nombre() const
{
  return "productos";
}


/*!
    \fn productos::formsPreferencias()
 */
QWidgetList productos::formsPreferencias()
{
 return QWidgetList();
}


/*!
    \fn productos::inicializar( QSettings *pref )
 */
bool productos::inicializar( QSettings *pref )
{
 _pref = pref;
 _acciones.clear();

 ActProductos = new QAction( "Ver Productos", this );
 ActProductos->setIcon( QIcon( ":/imagenes/productos.png" ) );
 ActProductos->setStatusTip( "Ver la lista de todos los productos" );
 ActProductos->setToolTip( "Ver la lista de prodcutos" );
 connect( ActProductos, SIGNAL( triggered() ), this, SLOT( verProductos() ) );

 _acciones.append( ActProductos );

 return verificarTablas();
}


/*!
    \fn productos::verificarTablas()
 */
bool productos::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "producto" ) )
 { qWarning( "Error al buscar la tabla producto" ); return false; }
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
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  menuHer->addAction( ActProductos );
 }
}


/*!
    \fn productos::version() const
 */
double productos::version() const
{
 return 0.1;
}

QSettings *productos::pref()
{
 return _pref;
}


/*!
    \fn productos::verProductos()
 */
void productos::verProductos()
{ emit agregarVentana( new VProductos( ) ); }


/*!
    \fn productos::crearToolBar( QToolBar *t )
 */
void productos::crearToolBar( QToolBar *t )
{
    /// @todo implement me
}
