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
#include "formresumenctacte.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <QSqlError>
#include "eactcerrar.h"
#include "eactimprimir.h"
#include "eactemail.h"
#include "eactpdf.h"
#include "mitemcuentacorriente.h"

FormResumenCtaCte::FormResumenCtaCte ( QWidget* parent, Qt::WFlags fl )
: EVentana ( parent, fl ), Ui::FormResumenCtaCteBase()
{
	setupUi ( this );
	this->setObjectName( "Resumen_cuenta-cte" );
	this->setWindowTitle( "Resumen de Cta Cte" );

	// Relleno el combobox
	QSqlQuery cola( "SELECT cc.numero_cuenta, c.razon_social FROM ctacte AS cc, clientes AS c WHERE cc.id_cliente = c.id AND fecha_baja IS NOT NULL" );
	while( cola.next() )
	{
		CBClienteCtaCte->insertItem( cola.record().value(0).toInt(),
					     "#" + cola.record().value(0).toString() + " - " + cola.record().value(1).toString(),
					     cola.record().value(0).toString() );
	}
	CBClienteCtaCte->setEditable( true );
	CBClienteCtaCte->setCurrentIndex( -1 );
 	connect( CBClienteCtaCte, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCtaCte( int ) ) );

	this->addAction( new EActCerrar( this ) );

	EActImprimir *ActImprimir = new EActImprimir( this );
	connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );
	this->addAction( ActImprimir );

	EActPdf *ActPdf = new EActPdf( this );
	this->addAction( ActPdf );
	connect( ActPdf, SIGNAL( triggered() ), this, SLOT( pdf() ) );

	EActEmail *ActEmail = new EActEmail( this );
 	this->addAction( ActEmail );
	connect( ActEmail, SIGNAL( triggered() ), this, SLOT( email() ) );

	modeloItem = new MItemCuentaCorriente( TVItems );
	TVItems->setModel( modeloItem );
	TVItems->hideColumn( 0 );
	TVItems->hideColumn( 2 );
	TVItems->hideColumn( 7 );



}

FormResumenCtaCte::~FormResumenCtaCte()
{
}


/*!
    \fn FormResumenCtaCte::setNumeroCuenta( const QString &numero_cuenta )
	Setea todas las condiciones del formulario para mostrar los datos de la cuenta corriente seleccionada por el parametro
	@param numero_cuenta Numero de cuenta al que se desea ver el resumen
 */
void FormResumenCtaCte::setNumeroCuenta( const int &numero_cuenta )
{
 // Seteo el numero de cuenta
 CBClienteCtaCte->setCurrentIndex( numero_cuenta );
 //Busco los datos
 QSqlQuery cola( QString( "SELECT fecha_alta, saldo, limite FROM ctacte WHERE numero_cuenta = '%1'" ).arg( numero_cuenta ) );
 if( cola.next() )
 {
   LFechaAlta->setText( cola.record().value(0).toDate().toString() );
   LSaldoActual->setText( QString( "$ %L1" ).arg( cola.record().value(1).toDouble() ) );
   LLimiteCredito->setText( QString( "$ %L1" ).arg( cola.record().value(2).toDouble() ) );
   modeloItem->setFilter( QString( "numero_cuenta = %1" ).arg( numero_cuenta ) );
   modeloItem->select();
 }
 else
 {
  qWarning( "Error al obtener los datos de la cuenta corriente" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.executedQuery() ) );
 }
}


/*!
    \fn FormResumenCtaCte::cambioCtaCte( int numero_cuenta )
	Slot llamado cada vez que se cambia el combobox de la cuenta corriente
	@param numero_cuenta Numero de cuenta que indica el combobox
 */
void FormResumenCtaCte::cambioCtaCte( int numero_cuenta )
{
 setNumeroCuenta( CBClienteCtaCte->itemData( CBClienteCtaCte->currentIndex(), Qt::EditRole ).toInt() );
}


/*!
    \fn FormResumenCtaCte::imprimir()
 */
void FormResumenCtaCte::imprimir()
{ return;
    /// @todo implement me
}
