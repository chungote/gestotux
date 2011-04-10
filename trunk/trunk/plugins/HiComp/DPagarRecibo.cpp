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

DPagarRecibo::DPagarRecibo(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->setObjectName( "DPagarRecibo" );
    //this->setIcon( QIcon( ":/imagenes/pagorecibo.png" ) );

    this->adjustSize();

    // Guardo la serie y numero de recibo para referencia futura
    this->_num_recibo = MPagos::buscarMenorSerieNumeroPagado();

    // Busco el minimo numero de recibo que tiene el pagado puesto y lo coloco como minimo
    this->SBNumeroRecibo->setMinimum( this->_num_recibo.second );

    // Conecto la señal para que al colocar el numero de recibo se pueda buscar si esta pagado o no, y actualizar los datos
    connect( this->SBNumeroRecibo, SIGNAL( valueChanged( int ) ), this, SLOT( cambioNumeroRecibo( int ) ) );


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
void DPagarRecibo::accept()
{
    QMessageBox::critical( this, "error", "No implementado" );
    abort();
    // busco si el recibo esta como pagado o no
    MPagos *m = new MPagos();
    if( m->buscarSiPagado( this->_num_recibo.first, this->SBNumeroRecibo->value() ) ) {
        QMessageBox::warning( this, "Ya pagado", QString( "El recibo %1-%2 ya esta como pagado en la base de datos." ).arg( this->_num_recibo.first ).arg( this->_num_recibo.second ) );
        delete m;
        return;
    }
    // El recibo no esta pagado. Lo intento poner como pagado.
    if( m->setearComoPagado( m->buscarIdPorSerieNumero( this->_num_recibo ) ) ) {
        QMessageBox::information( this, "Correcto", QString( "El recibo %1-%2 fue puesto como pagado y fue descontado de la cuenta corriente del cliente" ).arg( this->_num_recibo.first ).arg( this->_num_recibo.second ) );
    } else {
        QMessageBox::warning( this, "Error", "No se pudo poner como pagado. Verifique debug.txt" );
        delete m;
        return;
    }
    delete m;
    QDialog::accept();
}

void DPagarRecibo::reject()
{
    QMessageBox::critical( this, "error", "No implementado" );
    abort();
    QDialog::accept();
}
