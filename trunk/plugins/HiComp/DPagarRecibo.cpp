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

DPagarRecibo::DPagarRecibo(QWidget *parent) :
    QDialog(parent), _num_recibo( 0, -1, -1 )
{
    setupUi(this);
    this->setObjectName( "DPagarRecibo" );
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
/*!
 * \fn DPagarRecibo::accept()
 * Funciòn llamada cuando se le da OK al dialogo, verifica que el recibo no este pagado ya y lo pone como pagado si no lo esta. En caso de falla muestra el error pero no se cierra.
 */
void DPagarRecibo::accept()
{
    QMessageBox::critical( this, "error", "No implementado" );
    /*abort();
    // busco si el recibo esta como pagado o no
    MPagos *m = new MPagos();
    if( m->buscarSiPagado( this->_num_recibo.serie(), this->SBNumeroRecibo->value() ) ) {
        QMessageBox::warning( this, "Ya pagado", QString( "El recibo %1 ya esta como pagado en la base de datos." ).arg( this->_num_recibo.aCadena() ) );
        delete m;
        return;
    }
    // El recibo no esta pagado. Lo intento poner como pagado.
    if( m->setearComoPagado( m->buscarIdPorSerieNumero( this->_num_recibo ), CkBEfectivo->isChecked() ) ) {
        QMessageBox::warning( this, "Error", "Verificar si es un recibo de un servicio para conocer los recargos!!!" );
        abort();
        QMessageBox::information( this, "Correcto", QString( "El recibo %1 fue puesto como pagado y fue descontado de la cuenta corriente del cliente" ).arg( this->_num_recibo.aCadena() ) );
    } else {
        QMessageBox::warning( this, "Error", "No se pudo poner como pagado. Verifique debug.txt" );
        delete m;
        return;
    }
    delete m;*/
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
  // Coloco automaticamente el importe en a pagar
  DSBPagar->setValue( DSBImporte->value() );
}

/*!
 * \fn DPagarRecibo::cambioAPagar( double cantidad )
 * slot llamado cuando se cambia la cantidad a pagar
 */
void DPagarRecibo::cambioAPagar( double /*cantidad*/ )
{ DSBSaldo->setValue( DSBImporte->value() - DSBPagar->value() ); }
