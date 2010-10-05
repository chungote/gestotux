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
#include <QPaintEngine>

FormPantallaInicial::FormPantallaInicial(QWidget *parent) :
    EVentana(parent)
{
    setupUi(this);
    this->setObjectName( "inicio" );
    this->setWindowTitle( "Inicio" );
    this->setWindowIcon( QIcon( ":/imagenes/inicio.png" ) );

    // Seteo los iconos
    //TBPresupuestos->setIcon( QIcon( ":/imagenes/presupuesto.png" ) );
    TBCaja->setIcon( QIcon( ":/imagenes/caja.png" ) );
    TBClientes->setIcon( QIcon( ":/imagenes/clientes.png" ) );
    TBCompras->setIcon( QIcon( ":/imagenes/compras.png" ) );
    TBProductos->setIcon( QIcon( ":/imagenes/productos.png" ) );
    TBCuentasCorrientes->setIcon( QIcon( ":/imagenes/ctacte.png" ) );
    TBProveedores->setIcon( QIcon( ":/imagenes/proveedores.png" ) );
    TBServicios->setIcon( QIcon( ":/imagenes/servicios.png" ) );
    TBGastos->setIcon( QIcon( ":/imagenes/gastos.png" ) );
    // Generales
    TBBackup->setIcon( QIcon( ":/imagenes/backup.png" ) );
    TBPreferencias->setIcon( QIcon( ":/imagenes/configure.png" ) );

    // Conecto los slots
    connect( TBCaja        , SIGNAL( clicked() ), this, SLOT( caja()         ) );
    connect( TBBackup      , SIGNAL( clicked() ), this, SLOT( backup()       ) );
    connect( TBPreferencias, SIGNAL( clicked() ), this, SLOT( preferencias() ) );

    // Dibujo las flechas
    f1->setearOrigen( TBPresupuestos );
    f1->setearDestino( TBFacturas );
    f1->setearTamFlecha( 2 );
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

void FormPantallaInicial::caja()
{
}

#include "ebackup.h"
void FormPantallaInicial::backup()
{ emit agregarVentana( new Ebackup( this ) ); }

#include "formpreferencias.h"
void FormPantallaInicial::preferencias()
{ emit agregarVentana( new FormPreferencias( ) ); }

/*
void FormPantallaInicial::paintEvent( QPaintEvent *event )
{
    QPainter p( this );
    // Dibujo las lineas y flechas
    QLine l = f1->linea1();
    p.drawLine( l.p1(), l.p2() );
    l = f1->linea2();
    p.drawLine( l.p1(), l.p2() );
    l = f1->linea3();
    p.drawLine( l.p1(), l.p2() );
    p.end();
}
*/
