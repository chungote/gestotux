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
    MCOrigen = new MCajas( this );
    CBOrigen->setModel( MCOrigen );
    CBOrigen->setModelColumn( 1 );
    MCOrigen->select();

    MCDestino = new MCajas( this );
    CBDestino->setModel( MCDestino );
    CBDestino->setModelColumn( 1 );
    MCDestino->select();

    connect( CBDestino, SIGNAL( currentIndexChanged( int ) ), this,SLOT( cambioCajaDestino( int ) ) );
    connect( CBOrigen, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCajaOrigen( int ) ) );

    DSBCantidad->setMinimum( 0.0 );
}

void FormTransferir::setearCajaOrigen( const int id_caja )
{
    // como hacer el mappeo inverso?
    MCOrigen->setFilter( QString( " id_caja = %1" ).arg( id_caja ) );
    MCOrigen->select();
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

void FormTransferir::cambioCajaDestino( int indiceDestino )
{
     CBOrigen->disconnect( this, SLOT( cambioCajaOrigen( int ) ) );
     CBDestino->disconnect( this, SLOT( cambioCajaDestino( int ) ) );
     // Busco el ID que se selecciono para filtrar el otro modelo
     int id_destino = CBDestino->model()->data( CBDestino->model()->index( indiceDestino, 0 ), Qt::EditRole ).toInt();
     //qDebug( QString( "Filtrando caja: %1 ").arg( id_destino ).toLocal8Bit() );
     MCOrigen->setFilter( QString( "id_caja NOT IN ( %1 )" ).arg( id_destino ) );
     MCDestino->setFilter( "" );
     MCOrigen->select();
     MCDestino->select();
     CBDestino->setCurrentIndex( indiceDestino );
     connect( CBDestino, SIGNAL( currentIndexChanged( int ) ), this,SLOT( cambioCajaDestino( int ) ) );
     connect( CBOrigen, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCajaOrigen( int ) ) );
}

void FormTransferir::cambioCajaOrigen( int indiceOrigen )
{
        CBOrigen->disconnect( this, SLOT( cambioCajaOrigen( int ) ) );
        CBDestino->disconnect( this, SLOT( cambioCajaDestino( int ) ) );
        // Busco el ID que se selecciono para filtrar el otro modelo
        int id_origen = CBOrigen->model()->data( CBOrigen->model()->index( indiceOrigen, 0 ), Qt::EditRole ).toInt();
        MCDestino->setFilter( QString( "id_caja NOT IN ( %1 )" ).arg( id_origen ) );
        MCOrigen->setFilter( "" );
        MCOrigen->select();
        MCDestino->select();
        CBOrigen->setCurrentIndex( indiceOrigen );
        connect( CBDestino, SIGNAL( currentIndexChanged( int ) ), this,SLOT( cambioCajaDestino( int ) ) );
        connect( CBOrigen, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCajaOrigen( int ) ) );

}

void FormTransferir::transferir()
{
    // Controlo que la cantidad no sea cero
    if( DSBCantidad->value() <= 0.0 ) {
        QMessageBox::information( this, "Error", "No se puede realizar una transferencia de cantidad 0.0" );
        return;
    }
    // veo el saldo de la caja
    double saldo = MCajas::saldo( CBOrigen->model()->data( CBOrigen->model()->index( CBOrigen->currentIndex(), 0 ), Qt::EditRole ).toInt() );
    if( DSBCantidad->value() > saldo ) {
        QMessageBox::critical( this, "Error", "El saldo de la caja es insuficiente para la cantidad requerida a transferir" );
        return;
    }
    // Hago la transferencia
    int id_destino = CBDestino->model()->data( CBDestino->model()->index( CBDestino->currentIndex(), 0 ), Qt::EditRole ).toInt();
    int id_origen = CBOrigen->model()->data( CBOrigen->model()->index( CBOrigen->currentIndex(), 0 ), Qt::EditRole ).toInt();
    /// Registro el movimiento
    QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
    MMovimientosCaja *mv = new MMovimientosCaja();
    if( !mv->agregarMovimiento( id_origen, "Transferencia entre cajas", QString(), 0.0, DSBCantidad->value() ) ) {
        QMessageBox::critical( this, "Error", "No se puede registrar el movimiento de salida en la caja de origen" );
        QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
        return;
    }
    if( !mv->agregarMovimiento( id_destino, "Transferencia entre cajas", QString(), DSBCantidad->value(), 0.0 ) ) {
        QMessageBox::critical( this, "Error", "No se pudo registrar el movimiento de entrada en la caja de destino" );
        QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
        return;
    }
    QSqlDatabase::database( QSqlDatabase::defaultConnection, false  ).commit();
    QMessageBox::information( this, "Correcto", "La transferencia fue registrada correctamente" );
    this->close();
}
