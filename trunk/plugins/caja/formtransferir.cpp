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

#include "formtransferir.h"

#include "mcajas.h"
#include "mmovimientoscaja.h"
#include <QSqlDatabase>

#include <QMessageBox>

FormTransferir::FormTransferir(QWidget *parent) :
    QDialog( parent ){
    setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose );
    this->setWindowTitle( "Transferencia" );

    // seteo los botones
    PBAceptar->setText( "Transferir" );
    //PBAceptar->setIcon( QIcon( ":/imagenes/" ) );
    connect( PBAceptar, SIGNAL( clicked() ), this, SLOT( transferir() ) );

    PBCancelar->setText( "Cancelar" );
    PBCancelar->setIcon( QIcon( ":/imagenes/stop.png" ) );
    connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( close() ) );

    // Creo los modelos interdependientes
    CBOrigen->setearTabla( "caja" );
    CBOrigen->setearCampoId( "id_caja" );
    CBOrigen->setearCampoTexto( "nombre" );

    CBDestino->setearTabla( "caja" );
    CBDestino->setearCampoId( "id_caja" );
    CBDestino->setearCampoTexto( "nombre" );

    CBDestino->setCurrentIndex( -1 );
    CBOrigen->setCurrentIndex( -1 );

    connect( CBDestino, SIGNAL( cambioId( int ) ), this,SLOT( cambioCajaDestino( int ) ) );
    connect( CBOrigen, SIGNAL( cambioId( int ) ), this, SLOT( cambioCajaOrigen( int ) ) );

    DSBCantidad->setMinimum( 0.0 );

}

void FormTransferir::setearCajaOrigen( const int id_caja )
{
    CBDestino->setearFiltro( "" );
    CBOrigen->setearId( id_caja );
    CBDestino->setearFiltro( QString( " id_caja = %1" ).arg( id_caja ) );

}

void FormTransferir::setearCajaDestino( const int id_caja )
{
    CBDestino->setearFiltro( "" );
    CBDestino->setearId( id_caja );
    CBOrigen->setearFiltro( QString( " id_caja = %1 " ).arg( id_caja ) );
}

void FormTransferir::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void FormTransferir::cambioCajaDestino( int id_caja )
{
     CBOrigen->disconnect( this, SLOT( cambioCajaOrigen( int ) ) );
     CBDestino->disconnect( this, SLOT( cambioCajaDestino( int ) ) );
     // Busco el ID que se selecciono para filtrar el otro modelo
     CBOrigen->setearFiltro( QString( "id_caja NOT IN ( %1 )" ).arg( CBDestino->idActual() ) );
     CBDestino->setearFiltro( "" );
     CBDestino->setCurrentIndex( id_caja );
     connect( CBDestino, SIGNAL( cambioId( int ) ), this,SLOT( cambioCajaDestino( int ) ) );
     connect( CBOrigen, SIGNAL( cambioId( int ) ), this, SLOT( cambioCajaOrigen( int ) ) );
}

void FormTransferir::cambioCajaOrigen( int id_caja )
{
        CBOrigen->disconnect( this, SLOT( cambioCajaOrigen( int ) ) );
        CBDestino->disconnect( this, SLOT( cambioCajaDestino( int ) ) );
        // Busco el ID que se selecciono para filtrar el otro modelo
        CBDestino->setearFiltro( QString( "id_caja NOT IN ( %1 )" ).arg( id_caja ) );
        CBOrigen->setearFiltro( "" );
        CBOrigen->setearId( id_caja );
        connect( CBDestino, SIGNAL( cambioId( int ) ), this,SLOT( cambioCajaDestino( int ) ) );
        connect( CBOrigen, SIGNAL( cambioId( int ) ), this, SLOT( cambioCajaOrigen( int ) ) );
        DSBCantidad->setMaximum( MCajas::saldo( id_caja ) );
}

void FormTransferir::transferir()
{
    // Controlo que la cantidad no sea cero
    if( DSBCantidad->value() <= 0.0 ) {
        QMessageBox::information( this, "Error", "No se puede realizar una transferencia de cantidad 0.0" );
        return;
    }
    // veo el saldo de la caja
    double saldo = MCajas::saldo( CBOrigen->idActual() );
    if( DSBCantidad->value() > saldo ) {
        QMessageBox::critical( this, "Error", "El saldo de la caja es insuficiente para la cantidad requerida a transferir" );
        return;
    }
    // Hago la transferencia
    int id_destino = CBDestino->idActual();
    int id_origen = CBOrigen->idActual();
    /// Registro el movimiento
    QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
    MMovimientosCaja *mv = new MMovimientosCaja();
    if( !mv->agregarMovimiento( id_origen, QString( "Transferencia hacia caja %1").arg( MCajas::nombreCaja( id_destino ) ), QString(), 0.0, DSBCantidad->value() ) ) {
        QMessageBox::critical( this, "Error", "No se puede registrar el movimiento de salida en la caja de origen" );
        QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
        return;
    }
    if( !mv->agregarMovimiento( id_destino, QString( "Transferencia desde caja  %1" ).arg( MCajas::nombreCaja( id_origen ) ), QString(), DSBCantidad->value(), 0.0 ) ) {
        QMessageBox::critical( this, "Error", "No se pudo registrar el movimiento de entrada en la caja de destino" );
        QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
        return;
    }
    QSqlDatabase::database( QSqlDatabase::defaultConnection, false  ).commit();
    QMessageBox::information( this, "Correcto", "La transferencia fue registrada correctamente" );
    this->close();
}
