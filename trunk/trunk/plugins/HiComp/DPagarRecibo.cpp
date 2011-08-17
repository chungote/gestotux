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
#include <QSqlDatabase>

DPagarRecibo::DPagarRecibo(QWidget *parent) :
    QDialog(parent), _num_recibo( 0, -1, -1 )
{
    setupUi(this);
    this->setObjectName( "DPagarRecibo" );
    this->setWindowTitle( "Pago de recibo diferido" );
    this->setWindowIcon( QIcon( ":/imagenes/pagorecibo.png" ) );

    this->adjustSize();

    // Guardo la serie y numero de recibo para referencia futura
    this->_num_recibo = MPagos::buscarMenorSerieNumeroPagado();

    // Busco el minimo numero de recibo que tiene el pagado puesto y lo coloco como minimo
    //this->SBNumeroRecibo->setMinimum( this->_num_recibo.numero() );
    //this->LNumero->setText( this->LNumero->text().append( QString::number( this->_num_recibo.serie() ) ) );

    // Conecto la señal para que al colocar el numero de recibo se pueda buscar si esta pagado o no, y actualizar los datos
    connect( LENumeroRecibo, SIGNAL( returnPressed() ), this, SLOT( cambioNumeroRecibo() ) );

    // Conecto la señal para que al poner la cantidad pagada o cambiarla se actualize el saldo
    connect( this->DSBPagar, SIGNAL( valueChanged( double ) ), this, SLOT( cambioAPagar( double ) ) );

}

void DPagarRecibo::changeEvent(QEvent *e)
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
    QMessageBox::critical( this, "error", "No implementado" );
    return;
    // busco si el recibo esta como pagado o no
    MPagos *m = new MPagos();
    if( m->buscarSiPagado( this->_num_recibo ) ) {
        QMessageBox::warning( this, "Ya pagado", QString( "El recibo %1 ya esta como pagado en la base de datos." ).arg( this->_num_recibo.aCadena() ) );
        delete m;
        return;
    }
    QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
    // busco si corresponde a un recibo de servicio.
    int id_recibo = m->buscarIdPorSerieNumero( this->_num_recibo );
    MCobroServicioClientePeriodo *c = new MCobroServicioClientePeriodo();
    if( c->verificarIdFactura( id_recibo ) ) {
        c->colocarComoPagado( id_recibo, id_recibo );
    }
    // El recibo no esta pagado. Lo intento poner como pagado.
    if( m->setearComoPagado( id_recibo, CkBEfectivo->isChecked() ) ) {
        QMessageBox::warning( this, "¡Advertencia!", "Este sistema no esta considerando los recargos!!!" );
        QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).commit();
        QMessageBox::information( this, "Correcto", QString( "El recibo %1 fue puesto como pagado y fue descontado de la cuenta corriente del cliente" ).arg( this->_num_recibo.aCadena() ) );
    } else {
        QMessageBox::warning( this, "Error", "No se pudo poner como pagado. Verifique debug.txt" );
        QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
        delete c;
        delete m;
        return;
    }
    delete c;
    delete m;
    QDialog::accept();
}

/*!
 * \fn DPagarRecibo::cambioNumeroRecibo()
 * Slot llamado para cargar los datos recibo
 */
void DPagarRecibo::cambioNumeroRecibo()
{
  // Busco todos los datos y los pongo en los lugares correspondientes
  MPagos *m = new MPagos();
  NumeroComprobante *num = NumeroComprobante::desdeString( LENumeroRecibo->text() );
  if( m->buscarSiPagado( num ) ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "El recibo ya se encuentra pagado!" ) );
        delete m;
        return;
  }
  // Como no esta pagado, pongo el importe
  DSBImporte->setValue( m->buscarImporte( this->_num_recibo ) );
  // Buscar los recargos

  // Coloco automaticamente el importe en a pagar
  DSBPagar->setValue( DSBImporte->value() );
}

/*!
 * \fn DPagarRecibo::cambioAPagar( double cantidad )
 * slot llamado cuando se cambia la cantidad a pagar
 */
void DPagarRecibo::cambioAPagar( double /*cantidad*/ )
{ DSBSaldo->setValue( DSBImporte->value() - DSBPagar->value() ); }
