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
#include "botoneslaterales.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QIcon>

#include "digifauno.h"

BotonesLaterales::BotonesLaterales(QWidget* parent, Qt::WindowFlags f)
: QToolBox( parent, f )
{
 	// Casteo el objeto de ventana principal
	digifauno = qobject_cast<DigiFauno *>(this->parentWidget()->parentWidget());
    setObjectName( QString::fromUtf8( "TBacciones" ) );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Ppeluqueria = new QWidget();
    Ppeluqueria->setObjectName( QString::fromUtf8( "Ppeluqueria" ) );
    int id_pelu = addItem( Ppeluqueria, "Peluqueria Canina" );
    setItemIcon( id_pelu, QIcon( ":/imagenes/pelu.gif" ) );
    QVBoxLayout *layoutPeluqueria = new QVBoxLayout( Ppeluqueria );

    PBAgregarServicio = new QPushButton( Ppeluqueria );
    PBAgregarServicio->setText( "Agregar Nueva Servicio" );
    PBAgregarServicio->setIcon( QIcon( ":/imagenes/pelu.gif" ) );
    PBAgregarServicio->setFlat( true );
    layoutPeluqueria->addWidget( PBAgregarServicio );
    connect( PBAgregarServicio, SIGNAL( clicked() ), digifauno, SLOT( agregarServicioPeluqueria() ) );
    PBAgregarMascota = new QPushButton( Ppeluqueria );
    PBAgregarMascota->setText( "Agregar Nueva Mascota" );
    PBAgregarMascota->setIcon( QIcon( ":/imagenes/add.png" ) );
    PBAgregarMascota->setFlat( true );
    layoutPeluqueria->addWidget( PBAgregarMascota );
    connect( PBAgregarMascota, SIGNAL( clicked() ), digifauno, SLOT( agregarMascota() ) );
    PBMascotas = new QPushButton( Ppeluqueria );
    PBMascotas->setText( "Mascotas" );
    PBMascotas->setFlat( true );
    PBMascotas->setIcon( QIcon( ":/imagenes/mascotas.gif" ) );
    layoutPeluqueria->addWidget( PBMascotas );
    connect( PBMascotas, SIGNAL( clicked() ), digifauno, SLOT( mascotas() ) );
    PBDuenos = new QPushButton( Ppeluqueria );
    PBDuenos->setText( "Dueños" );
    PBDuenos->setFlat( true );
    PBDuenos->setIcon( QIcon( ":/imagenes/duenos.png" ) );
    layoutPeluqueria->addWidget( PBDuenos );
    connect( PBDuenos, SIGNAL( clicked() ), digifauno, SLOT( duenos() ) );
    QSpacerItem *espaciadorPeluqueria = new QSpacerItem( 10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
    layoutPeluqueria->addItem( espaciadorPeluqueria );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Seccion de ventas
    Pventas = new QWidget();
    Pventas->setObjectName( QString::fromUtf8( "Pventas" ) );
    int id_venta = addItem( Pventas, "Ventas" );
    setItemIcon( id_venta, QIcon( ":/imagenes/ventas.jpg" ) );
    QVBoxLayout *layoutVentas = new QVBoxLayout( Pventas );
    PBAgregarVenta = new QPushButton( Pventas );
    PBAgregarVenta->setIcon( QIcon( ":/imagenes/add.png" ) );
    PBAgregarVenta->setFlat(true);
    PBAgregarVenta->setText( "Agregar Venta" );
    connect( PBAgregarVenta, SIGNAL( clicked() ), digifauno, SLOT( agregar_venta() ) );
    layoutVentas->addWidget( PBAgregarVenta );
    PBProductos = new QPushButton( Pventas );
    PBProductos->setIcon( QIcon( ":/imagenes/productos.jpg" ) );
    PBProductos->setFlat(true);
    PBProductos->setText( "Productos" );
    layoutVentas->addWidget( PBProductos );
    connect( PBProductos, SIGNAL( clicked() ), digifauno, SLOT( productos() ) );
    QSpacerItem *espaciadorVentas = new QSpacerItem( 10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
    layoutVentas->addItem( espaciadorVentas );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Pcompras = new QWidget();
    Pcompras->setObjectName(QString::fromUtf8("Pcompras"));
    QVBoxLayout *layoutCompras = new QVBoxLayout( Pcompras );

    PBAgregarCompra = new QPushButton( Pcompras );
    PBAgregarCompra->setText( "Agregar Nueva Compra" );
    PBAgregarCompra->setIcon( QIcon( ":/imagenes/add.png" ) );
    PBAgregarCompra->setFlat( true );
    layoutCompras->addWidget( PBAgregarCompra );
    connect( PBAgregarCompra, SIGNAL( clicked() ), digifauno, SLOT( agregarCompra() ) );

    PBGastos = new QPushButton( Pcompras );
    PBGastos->setFlat( true );
    PBGastos->setText( "Agregar Gasto" );
    PBGastos->setIcon( QIcon( ":/imagenes/gasto.jpg" ) );
    layoutCompras->addWidget( PBGastos );
    connect( PBGastos, SIGNAL( clicked() ), digifauno, SLOT( agregar_gasto() ) );

    PBVerProveedores = new QPushButton( Pcompras );
    PBVerProveedores->setText( "Proveedores" );
    PBVerProveedores->setIcon( QIcon( ":/imagenes/proveedores.jpg" ) );
    PBVerProveedores->setFlat( true );
    layoutCompras->addWidget( PBVerProveedores );
    connect( PBVerProveedores, SIGNAL( clicked() ), digifauno, SLOT( proveedores() ) );

    QPushButton *PBVerProductos = new QPushButton( Pcompras );
    PBVerProductos->setIcon( QIcon( ":/imagenes/productos.jpg" ) );
    PBVerProductos->setFlat(true);
    PBVerProductos->setText( "Productos" );
    connect( PBVerProductos, SIGNAL( clicked() ), digifauno, SLOT( productos() ) );
    layoutCompras->addWidget( PBVerProductos );

    PBCategorias = new QPushButton( Pcompras );
    PBCategorias->setText( "Categorias" );
    PBCategorias->setFlat( true );
    PBCategorias->setIcon( QIcon( ":/imagenes/categorias.jpg" ) );
    layoutCompras->addWidget( PBCategorias );
    connect( PBCategorias, SIGNAL( clicked() ), digifauno, SLOT( categorias() ) );

    QSpacerItem *espaciadorCompras = new QSpacerItem( 10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
    layoutCompras->addItem( espaciadorCompras );
    int id_compras = addItem( Pcompras, "Compras y Gastos" );
    setItemIcon( id_compras, QIcon( ":/imagenes/compras.jpg" ) );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Presumenes = new QWidget();
    Presumenes->setObjectName( QString::fromUtf8( "Presumenes" ) );
    int id_res = addItem( Presumenes, "Resumenes" );
    setItemIcon( id_res, QIcon( ":/imagenes/resumenes.png" ) );

    QVBoxLayout *layoutResumenes = new QVBoxLayout( Presumenes );
    layoutResumenes->setObjectName( "layoutResumenes" );
    PBResumenDiario = new QPushButton( Presumenes );
    PBResumenDiario->setText( "Resumen Diario" );
    PBResumenDiario->setFlat( true );
    PBResumenDiario->setToolTip( "Ver resumen detallado para el dia de hoy" );
    PBResumenDiario->setIcon( QIcon( ":/imagenes/diario.png" ) );
    connect( PBResumenDiario, SIGNAL( clicked() ), digifauno, SLOT( resumenDiario() ) );
    layoutResumenes->addWidget( PBResumenDiario );

    PBResumenSemanal = new QPushButton( Presumenes );
    PBResumenSemanal->setText( "Resumen Semanal" );
    PBResumenSemanal->setIcon( QIcon( ":/imagenes/semanal.png" ) );
    PBResumenSemanal->setFlat( true );
    connect( PBResumenSemanal, SIGNAL( clicked() ), digifauno, SLOT( resumen_semanal() ) );
    layoutResumenes->addWidget( PBResumenSemanal );
    PBResumenMensual = new QPushButton( Presumenes );
    PBResumenMensual->setText( "Resumen Mensual" );
    PBResumenMensual->setFlat( true );
    PBResumenMensual->setIcon( QIcon( ":/imagenes/mensual.png" ) );
    connect( PBResumenMensual, SIGNAL( clicked() ), digifauno, SLOT( resumenMensual() ) );
    layoutResumenes->addWidget( PBResumenMensual );
    PBResumenAnual = new QPushButton( Presumenes );
    PBResumenAnual->setText( "Resumen Anual" );
    PBResumenAnual->setFlat( true );
    connect( PBResumenAnual, SIGNAL( clicked() ), digifauno, SLOT( resumenAnual() ) );
    layoutResumenes->addWidget( PBResumenAnual );
    QSpacerItem *separadorResumenes = new QSpacerItem( 10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
    layoutResumenes->addItem( separadorResumenes );

	this->setMinimumWidth( 200 );

}


BotonesLaterales::~BotonesLaterales()
{
}
