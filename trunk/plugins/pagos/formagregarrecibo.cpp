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
#include "formagregarrecibo.h"
#include "emcliente.h"
#include "preferencias.h"
#include "definiciones.h"
#include "eregistroplugins.h"
#include "../CtaCte/mcuentacorriente.h"
#include "eactcerrar.h"
#include "eactguardar.h"
#include "mpagos.h"

#include <QMessageBox>

#include "openreports.h"
#include "common/parameter.h"

FormAgregarRecibo::FormAgregarRecibo ( QWidget* parent, Qt::WFlags fl )
: EVentana( parent, fl ), Ui::FormReciboBase()
{
        setupUi ( this );

        setObjectName( "agregar_recibo" );
        setWindowTitle( "Nuevo recibo" );
        setWindowIcon( QIcon( ":/imagenes/recibos.png" ) );

        CBCliente->setModel( new EMCliente( CBCliente ) );
        CBCliente->setModelColumn( 1 );
        CBCliente->setCurrentIndex( -1 );

        connect( CBCliente, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCliente( int ) ) );
        connect( dSBPagado, SIGNAL( valueChanged( double ) ), this, SLOT( cambioPagado( double ) ) );

        this->addAction( new EActGuardar( this ) );
        this->addAction( new EActCerrar( this ) );

        // Seteo la fecha a la de hoy
        this->DEFecha->setDate( QDate::currentDate() );
        // Coloco el numero de recibo al hacer set del modelo
        RBContado->setEnabled(false);
}

FormAgregarRecibo::~FormAgregarRecibo()
{
}


/*!
  \fn FormAgregarRecibo::setearModelo( MPagos *m )
  Setea el modelo que se utilizará para agregar los datos  que se actualize en la vista
  @param m Modelo de pagos ( clase @MPagos )
 */
void FormAgregarRecibo::setearModelo( MPagos *m )
{
    if( m!=0 ) {
        this->_modelo = m;
    } else {
        this->_modelo = new MPagos( this );
    }
    // Busco el ultimo numero de recibo
    this->LENumero->setText( QString( "%L1" ).arg( this->_modelo->buscarUltimoNumeroRecibo() + 1 ) );
}

/*!
    \fn FormAgregarRecibo::recalcularTotal()
 */
void FormAgregarRecibo::recalcularTotal()
{
    if( dSBDeuda->value() > 0 ) {
        dSBTotal->setValue( dSBDeuda->value() - dSBPagado->value() );
    } else {
        dSBTotal->setValue( dSBPagado->value() );
    }

}


/*!
    \fn FormAgregarRecibo::cambioCliente( int id_combo )
 */
void FormAgregarRecibo::cambioCliente( int id_combo )
{
 // Si es un cliente existente veo si tiene saldo
 if( preferencias::getInstancia()->value( "Preferencias/CtaCte/habilitada" ).toBool() && ERegistroPlugins::getInstancia()->existePlugin( "ctacte" ) )
 {
  QString numero_cuenta =  MCuentaCorriente::obtenerNumeroCuentaCorriente( this->CBCliente->model()->data( this->CBCliente->model()->index( id_combo, 0), Qt::EditRole ).toInt() );
  if( numero_cuenta == E_CTACTE_BUSCAR_NUMEROCUENTA_CLIENTE_INVALIDO )
  {
   qDebug( "Numero de cuenta invalido" );
   return;
  }
  else
  {
   dSBDeuda->setValue( MCuentaCorriente::saldo( numero_cuenta ) );
   recalcularTotal();
   return;
  }
 }
}


/*!
    \fn FormAgregarRecibo::cambioPagado( double valor )
 */
void FormAgregarRecibo::cambioPagado( double valor )
{
 recalcularTotal();
}

/*!
  \fn FormAgregarRecibo::guardar()
 */
void FormAgregarRecibo::guardar()
{
    // Verificaciónes iniciales
    if( this->LENumero->text().isEmpty() ) {
        QMessageBox::warning( this, "Faltan datos", "Por favor verifique que exista el numero de recibo" );
        return;
    }
    if( this->CBCliente->currentIndex() == -1 ) {
        QMessageBox::warning( this, "Faltan datos", "Por favor verifique que un cliente este elegido" );
        return;
    }
    if( this->TETexto->contenido( Qt::PlainText ).isEmpty() ) {
        QMessageBox::warning( this, "Faltan datos", "Por favor verifique que el texto del recibo no este vacio" );
        return;
    }
    if( (!this->RBContado->isChecked()) && (!this->RBotro->isChecked()) ) {
        QMessageBox::warning( this, "Faltan datos", "Por favor verifique que haya elegido una forma de pago" );
        return;
    }
    if( this->dSBPagado->value() <= 0.0 ) {
        QMessageBox::warning( this, "Faltan datos", "Por favor verifique que haya ingresado una cantidad a pagar" );
        return;
    }
    // busco la fecha de la ultima factura y verifico que facturemos con fecha igual o mayor
    QDate fecha_ultima_factura = this->_modelo->buscarFechaUltimoRecibo();
    if( ( fecha_ultima_factura.isValid() ) && ( this->DEFecha->date() < fecha_ultima_factura ) ) {
        QMessageBox::warning( this, "Faltan datos", QString( "Por favor verifique que haya ingresado una fecha mayor o igual a %1" ).arg( fecha_ultima_factura.toString() ) );
        return;
    }
    ///@todo Ver porque no toma el id del modelo esto
    int id_cliente = this->CBCliente->model()->data( this->CBCliente->model()->index( this->CBCliente->currentIndex(), 0 ), Qt::UserRole ).toInt();
    qDebug( QString( "IDCliente=%1").arg(id_cliente).toLocal8Bit());
    QDate fecha = this->DEFecha->date();
    QString contenido = this->TETexto->contenido( Qt::AutoText );
    double total = this->dSBPagado->value();
    bool pagado = false;
    bool contado = false;
    if( this->RBContado->isChecked() ) {
        pagado = true;
        contado = true;
    } else if( this->RBotro->isChecked() ) {
        pagado = true;
    }
    // Genero la transacción
    QSqlDatabase::database().transaction();
    this->_modelo->setEditStrategy( QSqlTableModel::OnManualSubmit );
    int num_recibo = this->_modelo->agregarRecibo( 1 /* id_cliente */, fecha, contenido, total, pagado, contado );
    if( num_recibo == -1 ) {
        this->_modelo->revertAll();
        QSqlDatabase::database().rollback();
        QMessageBox::warning( this, "Error", QString( "Ocurrio un error al intentar guardar el recibo" ) );
        return;
    }
    this->_modelo->submitAll();
    QSqlDatabase::database().commit();
    // Imprimir el recibo
    QMessageBox::information( this, "Correcto", QString( "El recibo nº %1 se guardo correctamente y se ha enviado a imprimir automaticamente" ).arg( num_recibo ) );
    /// Imprimo el recibo
    ParameterList lista;
    lista.append( "id_recibo", num_recibo );
    //lista.append( "id_cliente", id_cliente );
    lista.append( "id_cliente", 1 );
    orReport *rep = new orReport( "recibo", lista );
    if( rep->isValid() ) {
        rep->print( 0, true, true );
        rep->exportToPDF( "/home/Esteban/test.pdf" );
    } else {
        rep->reportError( this );
        QMessageBox::information( this, "Eroor", QString( "No se pudo encontrar la definicion del informe. Contactese con el administrador." ) );
    }
    this->close();
    this->_modelo = 0;
    return;
}