/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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

#include <QtGui>

#include <QSqlDatabase>
#include "digifauno.h"
#include "barralateral.h"
#include "preferencias.h"
#include "vduenos.h"
#include "vcategorias.h"
#include "vproveedor.h"
#include "formagregarventa.h"
#include "vproductos.h"
#include "formagregarmasctoa.h"
#include "formagregarservicio.h"
#include "vmascota.h"
#include "eresumen.h"
#include "visorresumenes.h"
#include "formacercade.h"
#include "formagregargasto.h"
#include "vgastos.h"
#include "formlistapeluqueria.h"
#include "formagregarcompra.h"
#include "vcompras.h"

QSettings *DigiFauno::_pref = 0;

/*!
    \fn DigiFauno::duenos()
 */
void DigiFauno::duenos()
{ emit agregarVentana( new VDuenos() ); }


/*!
    \fn DigiFauno::categorias()
 */
void DigiFauno::categorias()
{ emit agregarVentana( new VCategorias() ); }


/*!
    \fn DigiFauno::agregar_venta()
 */
void DigiFauno::agregar_venta()
{ emit agregarVentana( new FormAgregarVenta() ); }


/*!
    \fn DigiFauno::proveedores()
 */
void DigiFauno::proveedores()
{ emit agregarVentana( new VProveedor() ); }


/*!
    \fn DigiFauno::productos()
 */
void DigiFauno::productos()
{ emit agregarVentana( new VProductos() ); }
 //v-> setWindowIcon( QIcon( ":/imagenes/productos.jpg" ) );


/*!
    \fn DigiFauno::agregarMascota()
 */
void DigiFauno::agregarMascota()
{ emit agregarVentana( new FormAgregarMascota() ); }
  //f->setWindowIcon( QIcon( ":/imagenes/mascotas.gif" ) );
  //f->showMaximized();


/*!
    \fn DigiFauno::agregarServicioPeluqueria()
 */
void DigiFauno::agregarServicioPeluqueria()
{  emit agregarVentana( new FormAgregarServicio() ); }
 // g->setWindowIcon( QIcon( ":/imagenes/pelu.gif" ) );


/*!
    \fn DigiFauno::mascotas()
 */
void DigiFauno::mascotas()
{ emit agregarVentana( new VMascota() ); }


/*!
    \fn DigiFauno::resumenDiario()
 */
void DigiFauno::resumenDiario()
{ emit agregarVentana( new EResumen( 0, EResumen::diario ) ); }


/*!
    \fn DigiFauno::agregarCompra()
 */
void DigiFauno::agregarCompra()
{ emit agregarVentana( new FormAgregarCompra() ); }
 //j->setWindowIcon( QIcon( ":/imagenes/add.png" ) );


/*!
    \fn DigiFauno::resumenMensual()
 */
void DigiFauno::resumenMensual()
{ emit agregarVentana( new EResumen( 0, EResumen::mensual ) );  }
 //k->setWindowIcon( QIcon( ":/imagenes/resumenes.png" ) );


/*!
    \fn DigiFauno::resumenAnual()
 */
void DigiFauno::resumenAnual()
{ emit agregarVentana( new EResumen( 0, EResumen::anual ) ); }
//k->setWindowIcon( QIcon( ":/imagenes/resumenes.png" ) );

/*!
    \fn DigiFauno::agregar_gasto()
 */
void DigiFauno::agregar_gasto()
{ emit agregarVentana( new FormAgregarGasto() ); }


/*!
    \fn DigiFauno::ver_gastos()
 */
void DigiFauno::ver_gastos()
{ emit agregarVentana( new VGastos() ); }


/*!
    \fn DigiFauno::resumen_semanal()
 */
void DigiFauno::resumen_semanal()
{ emit agregarVentana( new EResumen( 0, EResumen::semanal ) ); }
   //k->setWindowIcon( QIcon( ":/imagenes/resumenes.png" ) );

/*!
    \fn DigiFauno::ver_peluqueria()
 */
void DigiFauno::ver_peluqueria()
{ emit agregarVentana( new FormListaPeluqueria() ); }
 //l->setWindowIcon( QIcon( ":/imagenes/pelu.gif" ) );


/*!
    \fn DigiFauno::ver_compras()
 */
void DigiFauno::ver_compras()
{ emit agregarVentana( new VCompras() ); }


/*!
    \fn DigiFauno::nombre() const
 */
QString DigiFauno::nombre() const
{
 return "digifauno";
}


/*!
    \fn DigiFauno::version() const
 */
double DigiFauno::version() const
{
  return 0.4;
}


/*!
    \fn DigiFauno::inicializar( QSettings *pref )
 */
bool DigiFauno::inicializar( QSettings *pref )
{
 Q_INIT_RESOURCE(embebido);
 _pref = pref;
 _acciones.clear();
 // Acciones estandar
 ////////////////////////////////
 // Muestra los miembros
 ////////////////////////////////
 ActDuenos = new QAction( "Dueños", this );
 ActDuenos->setStatusTip( "Muestra todos los dueños" );
 ActDuenos->setIcon( QIcon( ":/imagenes/duenos.png" ) );
 connect( ActDuenos, SIGNAL( triggered() ), this, SLOT( duenos() ) );
 ////////////////////////////////
 // Muestra las categorias
 ////////////////////////////////
 ActCategorias = new QAction( "Categorias", this );
 ActCategorias->setStatusTip( "Muestra las categorias de productos que hay" );
 ActCategorias->setIcon( QIcon( ":/imagenes/categorias.jpg" ) );
 connect( ActCategorias, SIGNAL( triggered() ), this, SLOT( categorias() ) );
 ///////////////////////////////
 // Muestra los proveedores
 //////////////////////////////
 ActProveedores = new QAction( "Proveedores", this );
 ActProveedores->setStatusTip( "Mustra los distintos proveedores" );
 ActProveedores->setIcon( QIcon( ":/imagenes/proveedores.jpg" ) );
 connect( ActProveedores, SIGNAL( triggered() ), this, SLOT( proveedores() ) );
 ///////////////////////////////
 // Muestra los productos
 ///////////////////////////////
 ActProductos = new QAction(  "Productos", this );
 ActProductos->setStatusTip( "Muestra los productos" );
 ActProductos->setIcon( QIcon( ":/imagenes/productos.jpg" ) );
 connect( ActProductos, SIGNAL( triggered() ), this, SLOT( productos() ) );
 /////////////////////////////////////////////
 // Muestra el formulario de agregar mascotas
 /////////////////////////////////////////////
 ActAgregarMascota = new QAction( "Agregar Mascota", this );
 ActAgregarMascota->setStatusTip( "Agrega una nueva mascota" );
 connect( ActAgregarMascota, SIGNAL( triggered() ), this, SLOT( agregarMascota() ) );
 /////////////////////////////////////
 // Muestra la lista de mascotas
 /////////////////////////////////////
 ActMascotas = new QAction( "Ver Mascotas", this );
 ActMascotas->setStatusTip( "Ver todas las mascotas y sus dueños" );
 ActMascotas->setIcon( QIcon( ":/imagenes/mascotas.gif" ) );
 connect( ActMascotas, SIGNAL( triggered() ), this, SLOT( mascotas() ) );
 /////////////////////////////////////
 // Muestra los gastos
 /////////////////////////////////////
 ActGastos = new QAction( "Gastos", this );
 ActGastos->setStatusTip( "Ver la lista de gastos" );
 ActGastos->setIcon( QIcon( ":/imagenes/gasto.jpg" ) );
 connect( ActGastos, SIGNAL( triggered() ), this, SLOT( ver_gastos() ) );
 /////////////////////////////////////
 // Muestra los servicios de peluqueria
 /////////////////////////////////////
 ActPeluqueria = new QAction( "Servicios", this );
 ActPeluqueria->setIcon( QIcon( ":/imagenes/pelu.gif" ) );
 ActPeluqueria->setStatusTip( "Muestra todos los servicios prestados" );
 connect( ActPeluqueria, SIGNAL( triggered() ), this, SLOT( ver_peluqueria() ) );
 ////////////////////////////////////
 // Muestra las compras realizadas
 ////////////////////////////////////
 ActVentas = new QAction( "Compras", this );
//  ActVentas->setIcon( QIcon( ":/imagenes/nose.png" ) );
 ActVentas->setStatusTip( "Muestra el historial de compras" );
 connect( ActVentas, SIGNAL( triggered() ), this, SLOT( ver_compras() ) );

 return true;
}


/*!
    \fn DigiFauno::verificarTablas()
 */
bool DigiFauno::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "mascota" ) )
 { qWarning( "Error al buscar la tabla mascota" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "dueno" ) )
 { qWarning( "Error al buscar la tabla dueno" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "peluqueria" ) )
 { qWarning( "Error al buscar la tabla peluqueria" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "gastos" ) )
 { qWarning( "Error al buscar la tabla gastos" );	return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "ventas" ) )
 { qWarning( "Error al buscar la tabla ventas" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "ventas_productos" ) )
 { qWarning( "Error al buscar la tabla ventas_productos" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "proveedor" ) )
 { qWarning( "Error al buscar la tabla proveedor" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "compras" ) )
 { qWarning( "Error al buscar la tabla compras" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "compras_productos" ) )
 { qWarning( "Error al buscar la tabla compras_productos" ); return false; }
 return true;
}


/*!
    \fn DigiFauno::accionesBarra(9 const
 */
QList<QAction *> DigiFauno::accionesBarra() const
{
 return _acciones;
}


/*!
    \fn DigiFauno::directorioActualizaciones() const
 */
QString DigiFauno::directorioActualizaciones() const
{
 return "digifauno";
}


/*!
    \fn DigiFauno::directorioBackup() const
 */
QString DigiFauno::directorioBackup() const
{
 return "digifauno";
}


/*!
    \fn DigiFauno::nombrePrograma() const
 */
QString DigiFauno::nombrePrograma() const
{
  return "Digifauno  -  " + QString::number( version() );
}

#include "formprefopciones.h"
/*!
    \fn DigiFauno::formsPreferencias()
 */
QWidgetList DigiFauno::formsPreferencias()
{
  QWidgetList lista;
  lista.append( new FormPrefOpciones() );
  return lista;
}


/*!
    \fn DigiFauno::crearMenu( QMenuBar* m )
 */
void DigiFauno::crearMenu( QMenuBar* m )
{
QMenu *menuHerramientas = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHerramientas == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  menuHerramientas->addAction( ActDuenos );
  menuHerramientas->addAction( ActCategorias );
  menuHerramientas->addAction( ActProveedores );
  menuHerramientas->addAction( ActProductos );
  menuHerramientas->addAction( ActMascotas );
  menuHerramientas->addAction( ActGastos );
  menuHerramientas->addAction( ActPeluqueria );
  menuHerramientas->addAction( ActVentas );
 }
}


/*!
    \fn DigiFauno::iconoPrograma() const
 */
QIcon DigiFauno::iconoPrograma() const
{
  return QIcon( ":/imagenes/icono.png" );
}


/*!
    \fn DigiFauno::empresa() const
 */
QString DigiFauno::empresa() const
{
 return "Veterinaria \"El Fauno\"";
}


/*!
    \fn DigiFauno::companeros()
 */
QString DigiFauno::companeros()
{
 return "Daniel Sequeira";
}


/*!
    \fn DigiFauno::tipo() const
 */
int DigiFauno::tipo() const
{
 return EPlugin::info;
}

Q_EXPORT_PLUGIN2( digifauno, DigiFauno );
