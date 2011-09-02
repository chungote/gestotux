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

#include "FormPantallaInicial.h"
#include "EFlecha.h"
#include "eregistroplugins.h"
#include <QPaintEngine>

FormPantallaInicial::FormPantallaInicial(QWidget *parent) :
    EVentana(parent)
{
    setupUi(this);
    this->setObjectName( "inicio" );
    this->setWindowTitle( "Inicio" );
    this->setWindowIcon( QIcon( ":/imagenes/inicio.png" ) );

    // Seteo los iconos
    // Generales
    TBBackup->setIcon( QIcon( ":/imagenes/backup.png" ) );
    connect( TBBackup, SIGNAL( clicked() ), this, SLOT( backup() ) );

    TBPreferencias->setIcon( QIcon( ":/imagenes/configure.png" ) );
    connect( TBPreferencias, SIGNAL( clicked() ), this, SLOT( preferencias() ) );

    TBClientes->setIcon( QIcon( ":/imagenes/clientes.png" ) );
    connect( TBClientes, SIGNAL( clicked() ), this, SLOT( clientes() ) );

    this->TBNotas->setVisible( false );
    this->TBResumenCtaCte->setVisible( false );

    /////////////////////////////////////////////////////////////////////////////////////////////
    // ERegistroPlugins::getInstancia
    ////////////////////////////////////////////////////////////////////////////////////////////
    //  Presupuestos
    if( ERegistroPlugins::getInstancia()->existePlugin( "presupuesto" ) ) {
        connect( TBPresupuestos, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("presupuesto")->botonPantallaInicial(), SIGNAL(triggered()) );
        TBPresupuestos->setIcon(ERegistroPlugins::getInstancia()->plugin("presupuesto")->botonPantallaInicial()->icon() );
    } else {
        TBPresupuestos->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Caja
    if( ERegistroPlugins::getInstancia()->existePlugin( "caja" ) ) {
        connect( TBCaja, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("caja")->botonPantallaInicial(), SIGNAL(triggered()) );
        TBCaja->setIcon(ERegistroPlugins::getInstancia()->plugin("caja")->botonPantallaInicial()->icon() );
    } else {
        TBCaja->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Compras
    if( ERegistroPlugins::getInstancia()->existePlugin( "compras" ) ) {
        connect( TBCompras, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("compras")->botonPantallaInicial(), SIGNAL(triggered()) );
        TBCompras->setIcon(ERegistroPlugins::getInstancia()->plugin("compras")->botonPantallaInicial()->icon() );
    } else {
        TBCompras->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Productos
    if( ERegistroPlugins::getInstancia()->existePlugin( "productos" ) ) {
        connect( TBProductos, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("productos")->botonPantallaInicial(), SIGNAL(triggered()) );
        TBProductos->setIcon( ERegistroPlugins::getInstancia()->plugin("productos")->botonPantallaInicial()->icon() );
    } else {
        TBProductos->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Cuentas Corrientes
    if( ERegistroPlugins::getInstancia()->existePlugin( "ctacte" ) ) {
        if( ERegistroPlugins::getInstancia()->plugin("ctacte")->botonPantallaInicial() )
        { connect( TBCuentasCorrientes, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("ctacte")->botonPantallaInicial(), SIGNAL(triggered()) );
          TBCuentasCorrientes->setIcon( ERegistroPlugins::getInstancia()->plugin("ctacte")->botonPantallaInicial() ->icon());
        } else { qWarning( "Error de accion de cuenta corriente") ; }
    } else {
        TBCuentasCorrientes->setVisible( false );
        TBResumenCtaCte->setVisible( false );
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Proveedores
    if( ERegistroPlugins::getInstancia()->existePlugin( "proveedor" ) ) {
        TBProveedores->setIcon( ERegistroPlugins::getInstancia()->plugin("proveedor")->botonPantallaInicial()->icon() );
        connect( TBProveedores, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("proveedor")->botonPantallaInicial(), SIGNAL(triggered()) );
    } else {
        TBProveedores->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Servicios
    if( ERegistroPlugins::getInstancia()->existePlugin( "servicios" ) ) {
        TBServicios->setIcon( ERegistroPlugins::getInstancia()->plugin("servicios")->botonPantallaInicial()->icon() );
        connect( TBServicios, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("servicios")->botonPantallaInicial(), SIGNAL(triggered()) );
    } else {
        TBServicios->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Gastos
    if( ERegistroPlugins::getInstancia()->existePlugin( "gastos" ) ) {
        TBGastos->setIcon( ERegistroPlugins::getInstancia()->plugin("gastos")->botonPantallaInicial()->icon() );
        connect( TBGastos, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("gastos")->botonPantallaInicial(), SIGNAL(triggered()) );
    } else {
        TBGastos->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Pagos / Recibos
    if( ERegistroPlugins::getInstancia()->existePlugin( "pagos" ) ) {
        TBRecibos->setIcon( ERegistroPlugins::getInstancia()->plugin("pagos")->botonPantallaInicial()->icon() );
        connect( TBRecibos, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("pagos")->botonPantallaInicial(), SIGNAL(triggered()) );
    } else {
        TBRecibos->setVisible( false );
    }
    //////////////////////////////////////////////////////////////////////////////////
    // Ventas / Facturas
    if( ERegistroPlugins::getInstancia()->existePlugin( "ventas" ) ) {
        TBFacturas->setIcon( ERegistroPlugins::getInstancia()->plugin("ventas")->botonPantallaInicial()->icon() );
        connect( TBFacturas, SIGNAL( clicked() ), ERegistroPlugins::getInstancia()->plugin("ventas")->botonPantallaInicial(), SIGNAL(triggered()) );
    } else {
        TBFacturas->setVisible( false );
    }
    ///////////////////////////////////////////////////////////////////////////////////
    // Dibujo las flechas
   /* EFlecha *f1 = new EFlecha( this );
    f1->setearOrigen( TBPresupuestos );
    f1->setearDestino( TBFacturas );
    f1->setearTamFlecha( 5 );

    EFlecha *f2 = new EFlecha( this );
    f2->setearOrigen( TBFacturas );
    f2->setearDestino( TBRecibos );
    f2->setearTamFlecha( 5 );

    EFlecha *f3 = new EFlecha( this );
    f3->setearOrigen( TBFacturas );
    f3->setearDestino( TBCaja );
    f3->setearTamFlecha( 5 ); */
}

void FormPantallaInicial::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

#include "ebackup.h"
void FormPantallaInicial::backup()
{ emit agregarVentana( new Ebackup( this ) ); }

#include "formpreferencias.h"
void FormPantallaInicial::preferencias()
{ emit agregarVentana( new FormPreferencias( ) ); }

#include "vcliente.h"
void FormPantallaInicial::clientes()
{ emit agregarVentana( new VCliente()); }