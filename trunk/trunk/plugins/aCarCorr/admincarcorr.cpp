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
#include "admincarcorr.h"

#include <QSqlQuery>

QStackedWidget *AdminCarCorr::_formCen = 0;
QSettings *AdminCarCorr::_pref = 0;

QIcon AdminCarCorr::iconoPrograma() const
{
 return QIcon();
}

QString AdminCarCorr::directorioActualizaciones() const
{
 return "actualizaciones";
}

QString AdminCarCorr::directorioBackup() const
{
 return "admCarCorr";
}

QString AdminCarCorr::nombrePrograma() const
{
 return "Sistema Informatico para Caravanas Administracion Corrientes";
}

QList< QAction * > AdminCarCorr::accionesBarra() const
{
 return _acciones;
}

QString AdminCarCorr::nombre() const
{
 return "admincaravanascorrientes";
}

QWidgetList AdminCarCorr::formsPreferencias()
{
 return QWidgetList();
}

bool AdminCarCorr::inicializar(QStackedWidget* formCen, QSettings* pref)
{
 _formCen = formCen;
 _pref = pref;
 _acciones.clear();

 ActCategoria = new QAction( "Ver Categorias", this );
 ActCategoria->setIcon( QIcon( ":/imagenes/categoria.png" ) );
 ActCategoria->setStatusTip( "Muestra el listado de categorias de caravanas" );
 ActCategoria->setToolTip( "Muestra las categorias ( Ctrl + u )" );
 ActCategoria->setShortcut( QKeySequence( "Ctrl+u" ) );
 connect( ActCategoria, SIGNAL( triggered() ), this, SLOT( verCategorias() ) );
 
 ActEstablecimiento = new QAction( "Ver Establecimientos", this );
 ActEstablecimiento->setIcon( QIcon( ":/imagenes/establecimientos.png" ) );
 ActEstablecimiento->setStatusTip( "Muestra el listado de establecimientos" );
 ActEstablecimiento->setToolTip( "Muestra los establecimientos ( Ctrl + e )" );
 ActEstablecimiento->setShortcut( QKeySequence( "Ctrl+e" ) );
 connect( ActEstablecimiento, SIGNAL( triggered() ), this, SLOT( verEstablecimientos() ) );

 ActNuevoEstablecimiento = new QAction( "Agregar Establecimiento", this );
 ActNuevoEstablecimiento->setIcon( QIcon( ":/imagenes/add.png" ) );
 ActNuevoEstablecimiento->setStatusTip( "Agrega un nuevo establecimiento" );
 ActNuevoEstablecimiento->setToolTip( "Agrega un nuevo establecimiento" );
 connect( ActNuevoEstablecimiento, SIGNAL( triggered() ), this, SLOT( agregarEstablecimiento() ) );

 ActAgregarCompra = new QAction( "Agregar compra", this );
 ActAgregarCompra->setIcon( QIcon( ":/imagenes/add.png" ) );
 ActAgregarCompra->setStatusTip( "Agrega una nueva compra" );
 ActAgregarCompra->setToolTip( "Agrega una nueva compra" );
 connect( ActAgregarCompra, SIGNAL( triggered() ), this, SLOT( agregarCompra() ) );

 ActAgregarVenta = new QAction( "Nueva venta", this );
 connect( ActAgregarVenta, SIGNAL( triggered() ), this, SLOT( hacerVenta() ) );

 ActAgregarMudanza = new QAction( "Nueva mudanza", this );
 connect( ActAgregarVenta, SIGNAL( triggered() ), this, SLOT( hacerMudanza() ) );

 _acciones.append( ActAgregarVenta );
 _acciones.append( ActAgregarCompra );
 _acciones.append( ActAgregarMudanza );

 return verificarTablas();
}

bool AdminCarCorr::verificarTablas()
{
 QSqlQuery cola;
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_categorias' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_categorias" );
  return false;
 }
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_establecimientos' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_establecimientos" );
  return false;
 }
 return true;
}

double AdminCarCorr::version() const
{
 return 0.1;
}

int AdminCarCorr::tipo() const
{
 return EPlugin::info;
}

void AdminCarCorr::crearMenu(QMenuBar* m)
{
  QMenu *menuHer = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHer == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 { 
  QMenu *menuRecibos = menuHer->addMenu( "Establecimientos" );
  menuRecibos->addAction( ActEstablecimiento );
  menuRecibos->addAction( ActNuevoEstablecimiento );
  menuHer->addAction( ActCategoria );
  menuHer->addSeparator();
  menuHer->addAction( ActAgregarCompra );
 }
}

Q_EXPORT_PLUGIN2(admincaravanascorrientes, AdminCarCorr );

#include "vcategorias.h"
/*!
    \fn AdminCarCorr::verCategorias()
 */
void AdminCarCorr::verCategorias()
{
 VCategorias *f = new VCategorias( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


#include "vestablecimiento.h"
/*!
    \fn AdminCarCorr::verEstablecimientos()
 */
void AdminCarCorr::verEstablecimientos()
{
  VEstablecimiento *f = new VEstablecimiento( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}

#include "formagregar.h"
/*!
    \fn AdminCarCorr::agregarCompra()
 */
void AdminCarCorr::agregarCompra()
{
  FormAgregar *f = new FormAgregar( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}

#include "formmudanza.h"
/*!
    \fn AdminCarCorr::hacerMovimiento()
 */
void AdminCarCorr::hacerMovimiento()
{
 FormMudanza *f = new FormMudanza( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}

#include "formventa.h"
/*!
    \fn AdminCarCorr::hacerVenta()
 */
void AdminCarCorr::hacerVenta()
{
 FormVenta *f = new FormVenta( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}
