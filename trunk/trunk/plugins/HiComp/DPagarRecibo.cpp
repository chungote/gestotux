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

#include "DPagarRecibo.h"
#include "mpagos.h"
#include "NumeroComprobante.h"
#include "mrecargoshechos.h"

#include <QSqlDatabase>
#include <QPushButton>

DPagarRecibo::DPagarRecibo(QWidget *parent) :
    QDialog(parent), _num_recibo( 0, -1, -1 )
{
    setupUi(this);
    this->setObjectName( "DPagarRecibo" );
    this->setWindowTitle( "Pago de recibo diferido" );
    this->setWindowIcon( QIcon( ":/imagenes/pagorecibo.png" ) );

    this->adjustSize();

    // Conecto la señal para que al colocar el numero de recibo se pueda buscar si esta pagado o no, y actualizar los datos
    connect( LENumeroRecibo, SIGNAL( returnPressed() ), this, SLOT( cambioNumeroRecibo() ) );

    // Conecto la señal para que al poner la cantidad pagada o cambiarla se actualize el saldo
    connect( DSBPagar, SIGNAL( valueChanged( double ) ), this, SLOT( cambioAPagar( double ) ) );

    connect( PBPagar, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( reject() ) );

}

#include <QMessageBox>
#include "eregistroplugins.h"
#include "mcajas.h"
#include "mcuentacorriente.h"
#include "mcobroservicioclienteperiodo.h"
/*!
 * \fn DPagarRecibo::accept()
 * Funciòn llamada cuando se le da OK al dialogo, verifica que el recibo no este pagado ya y lo pone como pagado si no lo esta. En caso de falla muestra el error pero no se cierra.
 */
void DPagarRecibo::accept()
{
    if( !_num_recibo.esValido() ) {
        return;
    }
        bool ok = false;
    // busco si el recibo esta como pagado o no
    MPagos *m = new MPagos();
    if( !m->existe( _num_recibo ) ) {
        QMessageBox::warning( this, "Error", "El recibo ingresado no esta registrado o no ha sido emitido." );
        LENumeroRecibo->clear();
        delete m;
        return;
    }
    if( m->buscarSiPagado( _num_recibo.serie(), _num_recibo.numero() ) ) {
        QMessageBox::warning( this, "Ya pagado", QString( "El recibo %1 ya esta como pagado en la base de datos." ).arg( this->_num_recibo.aCadena() ) );
        LENumeroRecibo->clear();
    } else {
        QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
        // busco si corresponde a un recibo de servicio.
        int id_recibo = m->buscarIdPorSerieNumero( this->_num_recibo );
        MCobroServicioClientePeriodo *c = new MCobroServicioClientePeriodo();
        if( c->verificarIdFactura( id_recibo ) ) {
            c->colocarComoPagado( id_recibo, id_recibo );
        }
        // El recibo no esta pagado. Lo intento poner como pagado.
        if( m->setearComoPagado( id_recibo, CkBEfectivo->isChecked() ) ) {
            QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).commit();
            QMessageBox::information( this, "Correcto", QString( "El recibo %1 fue puesto como pagado y fue descontado de la cuenta corriente del cliente" ).arg( this->_num_recibo.aCadena() ) );
            ok = true;
        } else {
            QMessageBox::warning( this, "Error", "No se pudo poner como pagado. Verifique debug.txt" );
            QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
        }
        delete c;
    }
    delete m;
    if( ok ) { QDialog::accept(); } else { return; }
}

/*!
 * \fn DPagarRecibo::cambioNumeroRecibo()
 * Slot llamado para cargar los datos recibo
 */
void DPagarRecibo::cambioNumeroRecibo()
{
  // Busco todos los datos y los pongo en los lugares correspondientes
  this->_num_recibo.desdeString( LENumeroRecibo->text() );
  if( !_num_recibo.esValido() ) {
      qWarning( "Numero de recibo invalido" );
      return;
  }
  MPagos *m = new MPagos();
  if( !m->existe( _num_recibo ) ) {
      QMessageBox::warning( this, "Error", "El recibo ingresado no esta registrado o no ha sido emitido." );
      LENumeroRecibo->clear();
      delete m;
      return;
  }
  if( m->buscarSiPagado( _num_recibo.serie(), _num_recibo.numero() ) ) {      
        QMessageBox::warning( this, "Error", QString::fromUtf8( "El recibo ya se encuentra pagado!" ) );
        LENumeroRecibo->clear();
        delete m;
        return;
  }
  // Como no esta pagado, pongo el importe
  DSBImporte->setValue( m->buscarImporte( this->_num_recibo ) );
  // Buscar los recargos
  int id_recibo = m->buscarIdPorSerieNumero( this->_num_recibo );
  if( id_recibo == -1 ) {
      qWarning( "No se pudo encontrar el id para el recibo buscado" );
      return;
  }
  int id_periodo_servicio = MCobroServicioClientePeriodo::buscarIdPeriodoServicio( id_recibo );
  if( id_periodo_servicio == -2 ) {
      qWarning( "Error al recibo en cobros echos." );
      return;
  }
  if( id_periodo_servicio == -1 ) {
      qDebug( "No corresponde a ningun servicio. No buscando recargos." );
  } else {
    int id_cliente = m->buscarIdCliente( this->_num_recibo );
    double recargo = MRecargosHechos::buscarRecargoPorPeriodoServicio( id_periodo_servicio, id_cliente );
    DSBRecargos->setValue( recargo );
  }
  // Coloco automaticamente el importe en a pagar
  DSBPagar->setValue( DSBImporte->value() + DSBRecargos->value() );
  delete m;
  m = 0;
}

/*!
 * \fn DPagarRecibo::cambioAPagar( double cantidad )
 * slot llamado cuando se cambia la cantidad a pagar
 */
void DPagarRecibo::cambioAPagar( double /*cantidad*/ )
{ DSBSaldo->setValue( DSBImporte->value() + DSBRecargos->value() - DSBPagar->value() ); }
