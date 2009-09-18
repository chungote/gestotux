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

}

FormAgregarRecibo::~FormAgregarRecibo()
{
}




/*!
    \fn FormAgregarRecibo::recalcularTotal()
 */
void FormAgregarRecibo::recalcularTotal()
{
 dSBTotal->setValue( dSBDeuda->value() - dSBPagado->value() );
}


/*!
    \fn FormAgregarRecibo::cambioCliente( int id_combo )
 */
void FormAgregarRecibo::cambioCliente( int id_combo )
{
 // Si es un cliente existente veo si tiene saldo
 if( preferencias::getInstancia()->value( "Preferencias/CtaCte/habilitada" ).toBool() && ERegistroPlugins::getInstancia()->existePlugin( "ctacte" ) )
 {
  QString numero_cuenta =  MCuentaCorriente::obtenerNumeroCuentaCorriente( 0 );
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
 ///@todo Ver si poner el numero en texto en el campo de texto

}
