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
#include <QAction>
#include <QMenu>
#include "eactcerrar.h"
#include "eactimprimir.h"
#include "eactemail.h"
#include "eactpdf.h"
#include "mitemcuentacorriente.h"
#include "eregistroplugins.h"

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
		CBClienteCtaCte->addItem(     "#" + cola.record().value(0).toString() + " - " + cola.record().value(1).toString(),
					     cola.record().value(0).toString() );
	}
	CBClienteCtaCte->setEditable( true );
	CBClienteCtaCte->setCurrentIndex( -1 );
 	connect( CBClienteCtaCte, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCtaCte( int ) ) );

	EActImprimir *ActImprimir = new EActImprimir( this );
	connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );
	this->addAction( ActImprimir );

	EActPdf *ActPdf = new EActPdf( this );
	this->addAction( ActPdf );
	connect( ActPdf, SIGNAL( triggered() ), this, SLOT( pdf() ) );

	EActEmail *ActEmail = new EActEmail( this );
 	this->addAction( ActEmail );
	connect( ActEmail, SIGNAL( triggered() ), this, SLOT( email() ) );

	modeloItem = new MItemCuentaCorriente( TVItems, false );
	TVItems->setModel( modeloItem );
	TVItems->hideColumn( 0 );
	TVItems->hideColumn( 2 );
	TVItems->hideColumn( 7 );
	TVItems->setSelectionMode( QAbstractItemView::SingleSelection );
	TVItems->setSelectionBehavior( QAbstractItemView::SelectRows );
	TVItems->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
	TVItems->setTextElideMode( Qt::ElideRight );
	/// Menu contextual para cada operacion de la cuenta corriente
	connect( TVItems, SIGNAL( pressed( const QModelIndex & ) ), this, SLOT( menuContextual( const QModelIndex & ) ) );

	this->addAction( new EActCerrar( this ) );


}

FormResumenCtaCte::~FormResumenCtaCte()
{
}


/*!
    \fn FormResumenCtaCte::setNumeroCuenta( const int &numero_cuenta )
	Setea todas las condiciones del formulario para mostrar los datos de la cuenta corriente seleccionada por el parametro
	@param numero_cuenta Numero de cuenta al que se desea ver el resumen
 */
void FormResumenCtaCte::setNumeroCuenta( const int &numero_cuenta )
{
 // Seteo el numero de cuenta
 CBClienteCtaCte->setCurrentIndex( CBClienteCtaCte->findText( QString::number( numero_cuenta ), Qt::MatchContains ) );
 //Busco los datos
 QSqlQuery cola( QString( "SELECT fecha_alta, saldo, limite FROM ctacte WHERE numero_cuenta = '%1'" ).arg( numero_cuenta ) );
 if( cola.next() )
 {
   LFechaAlta->setText( cola.record().value(0).toDate().toString( Qt::DefaultLocaleShortDate ) );
   LSaldoActual->setText( QString( "$ %L1" ).arg( cola.record().value(1).toDouble() ) );
   LLimiteCredito->setText( QString( "$ %L1" ).arg( cola.record().value(2).toDouble() ) );
   modeloItem->setFilter( QString( "id_ctacte = '%1'" ).arg( numero_cuenta ) );
   modeloItem->select();
 }
 else
 {
  LFechaAlta->setText( "" );
  LSaldoActual->setText( "" );
  LLimiteCredito->setText( "" );
  qWarning( "Error al obtener los datos de la cuenta corriente" );
  qDebug( qPrintable( "Numero cuenta: " + QString::number( numero_cuenta ) ) );
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
 setNumeroCuenta( CBClienteCtaCte->itemData( CBClienteCtaCte->currentIndex(), Qt::UserRole ).toInt() );
}


/*!
    \fn FormResumenCtaCte::imprimir()
 */
void FormResumenCtaCte::imprimir()
{
    /// @todo implement me
}


/*!
    \fn FormResumenCtaCte::pdf()
 */
void FormResumenCtaCte::pdf()
{
    /// @todo implement me
}


/*!
    \fn FormResumenCtaCte::email()
 */
void FormResumenCtaCte::email()
{
    /// @todo implement me
}


/*!
    \fn FormResumenCtaCte::menuContextual( const QModelIndex &indice )
 */
void FormResumenCtaCte::menuContextual( const QModelIndex &indice )
{
 if( QApplication::mouseButtons() != Qt::RightButton )
 { return; }
   // Calculo la posicion en que esta el item
   QPoint posicion;
   posicion.setX( TVItems->columnViewportPosition( indice.column() ) );
   posicion.setY( TVItems->rowViewportPosition( indice.row() ) );
   QMenu *_menuContextual = new QMenu( this );
   // Pido el menu contextual a la clase que esta manejando la vista acutlamente

 // Veo que tipo de item es
 QModelIndex temp = indice.model()->index( indice.row(), 3 );
 switch( temp.data( Qt::EditRole ).toInt() )
 {
	case MItemCuentaCorriente::Factura:
	{
		if( ERegistroPlugins::getInstancia()->existePlugin( "pagos" ) )
 		{
			/// @todo Verificar si no esta pagada ya
			QAction *ActCrearRecibo = new QAction( this );
			ActCrearRecibo->setText( "Pagar esta factura..." );
			connect( ActCrearRecibo, SIGNAL( triggered() ), this, SLOT( pagarFactura() ) );
			_menuContextual->addAction( ActCrearRecibo );
		}

		QAction *ActVerFactura = new QAction( this );
		ActVerFactura->setText( "Ver esta factura" );
		connect( ActVerFactura, SIGNAL( triggered() ), this, SLOT( verFactura() ) );
		_menuContextual->addAction( ActVerFactura );
		break;
	}
	case MItemCuentaCorriente::Recibo:
	{
		if( ERegistroPlugins::getInstancia()->existePlugin( "pagos" ) )
		{
			QAction *ActVerRecibo = new QAction( this );
			ActVerRecibo->setText( "Ver Recibo..." );
			connect( ActVerRecibo, SIGNAL( triggered() ), this, SLOT( verRecibo() ) );
			_menuContextual->addAction( ActVerRecibo );

		}
		break;
	}
 }
 _menuContextual->addSeparator();

 if( ERegistroPlugins::getInstancia()->existePlugin( "pagos" ) )
 {
 	QAction *ActPagarTodo = new QAction( this );
 	ActPagarTodo->setText( "Pagar todo..." );
 	connect( ActPagarTodo, SIGNAL( triggered() ), this, SLOT( pagarTodo() ) );
 	_menuContextual->addAction( ActPagarTodo );
 }

 QAction *ActImprimirResumen = new QAction( this );
 ActImprimirResumen->setText( "Imprimir resumen de cuenta" );
 connect( ActImprimirResumen, SIGNAL( triggered() ), this, SLOT( imprimir() ) );
 _menuContextual->addAction( ActImprimirResumen );

 _menuContextual->addSeparator();
 _menuContextual->addAction( new EActCerrar( this ) );
 _menuContextual->popup( this->mapToGlobal( posicion ) );
}

/*!
    \fn FormResumenCtaCte::pagarTodo()
 */
void FormResumenCtaCte::pagarTodo()
{
    /// @todo implement me
}


/*!
    \fn FormResumenCtaCte::verFactura()
 */
void FormResumenCtaCte::verFactura()
{
    /// @todo implement me
}

#include "evisorinformes.h"
#include "recibo.h"
/*!
    \fn FormResumenCtaCte::verRecibo()
 */
void FormResumenCtaCte::verRecibo()
{
 Recibo *re = new Recibo( this );
 re->setIDPago( 0  ); /// @todo Poner id del recibo
 EVisorInformes *visor = new EVisorInformes( new QPrinter(), this );
// re->hacerRecibo();
 connect( visor, SIGNAL( paintRequested( QPrinter* ) ), re, SLOT( previsualizar( QPrinter * ) ) );
 agregarVentana( visor );
}


/*!
    \fn FormResumenCtaCte::pagarFactura()
 */
void FormResumenCtaCte::pagarFactura()
{
 // Verifico que la factura no este pagada

 // Genero un nuevo recibo con el total de la factura y en el detalle que paga la factura

 // Busco los detalles de la factura


}
