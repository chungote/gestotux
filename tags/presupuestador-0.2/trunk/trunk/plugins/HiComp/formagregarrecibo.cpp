/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
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
#include "mrecibo.h"
#include "visorrecibo.h"
#include "preferencias.h"

#include <QLocale>
#include <QLineEdit>
#include <QComboBox>
#include "emcliente.h"
#include "eeditor.h"
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlQuery>
#include <QRadioButton>
#include <QSqlError>
#include <QSettings>
#include <QDate>
#include <QStackedWidget>

FormAgregarRecibo::FormAgregarRecibo(QWidget *parent)
 : EVentana(parent), Ui_FormAgregarReciboBase()
{
 setupUi( this );
 setObjectName( "Nuevo Recibo" );
 setWindowTitle( "Nuevo Recibo" );
 setAttribute( Qt::WA_DeleteOnClose );

 recargo = 0;

 // Cargo los meses
 QLocale locale;
 for( int i = 1; i<=12; i++ )
 {
  CBMeses->addItem( locale.monthName( i, QLocale::LongFormat ) );
 }

 CBClientes->setModel( new EMCliente( CBClientes ) );
 CBClientes->setModelColumn( 1 );
 CBClientes->setCurrentIndex( 0 );

 // Pongo la fecha de hoy
 dEFechaPago->setDate( QDate::currentDate() );

 CBMeses->setEnabled( false );
 lmes->setEnabled( false );

 LETotal->setText( dSBImporte->text() );

 connect( cBPagoMes,  SIGNAL( stateChanged( int ) ), this, SLOT( cambioEstadoPagoMes( int ) ) );
 connect( cBRecargos, SIGNAL( stateChanged( int ) ), this, SLOT( cambioEstadoRecargos( int ) ) );
 connect( dSBImporte, SIGNAL( valueChanged( double ) ), this, SLOT( cambioImporte( double ) ) );

 ActGuardar = new QAction( "Guardar", this );
 ActGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
 ActGuardar->setStatusTip( "Guarda el formulario y lo muestra" );
 ActGuardar->setToolTip( "Guardar ( Ctrl + g )" );
 ActGuardar->setShortcut( QKeySequence( "ctrl+g" ) );
 connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );

 ActCancelar = new QAction( "Cancelar", this );
 ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 ActCancelar->setStatusTip( "Cancela los datos ingresados y no genera un recibo" );
 ActCancelar->setShortcut( QKeySequence( "Ctrl+c" ) );
 ActCancelar->setToolTip( "Cancela los datos ingresados y cierra la ventana ( Ctrl + c ) " );
 connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( close() ) );

 ActGuardarImprimir = new QAction( "Guardar e Imprimir", this );
 ActGuardarImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
 ActGuardarImprimir->setStatusTip( "Guarda los datos e imprime directamente el recibo" );
 ActGuardarImprimir->setToolTip( "Guarda los datos e imprime el recibo ( Ctrl + i ) " );
 ActGuardarImprimir->setShortcut( QKeySequence( "Ctrl+i" ) );
 connect( ActGuardarImprimir, SIGNAL( triggered() ), this, SLOT( guardarImprimir() ) );

 addAction( ActCancelar );
 addAction( ActGuardar );
 addAction( ActGuardarImprimir );

 TETexto = new EEditor( groupBox_2 );
 groupBox_2->layout()->addWidget( TETexto );
}


FormAgregarRecibo::~FormAgregarRecibo()
{
}




/*!
    \fn FormAgregarRecibo::nombre()
 */
QString FormAgregarRecibo::nombre()
{
  return "Nuevo Recibo";
}


/*!
    \fn FormAgregarRecibo::cambioEstadoPagoMes( int estado )
 */
void FormAgregarRecibo::cambioEstadoPagoMes( int estado )
{
 if( estado == Qt::Checked )
 {
  CBMeses->setEnabled( true );
  lmes->setEnabled( true );
 }
 else
 {
  CBMeses->setEnabled( false );
  lmes->setEnabled( false );
 }
}


/*!
    \fn FormAgregarRecibo::cambioEstadoRecargos( int estado )
 */
void FormAgregarRecibo::cambioEstadoRecargos( int estado )
{
 if( estado == Qt::Checked )
 {
  if( dEFechaPago->date().day() > 13 || dEFechaPago->date().day() <= 17 )
  {
   recargo = 0.05;
  }
  else if( dEFechaPago->date().day() >= 18 || dEFechaPago->date().day() <= 31 )
  {
   recargo = 0.07;
  }
  else
  {
   recargo = 0;
  }
 }
 else
 {
  recargo = 0;
 }
}


/*!
    \fn FormAgregarRecibo::recalcular()
 */
void FormAgregarRecibo::recalcular()
{
 LETotal->setText( QString().setNum( dSBImporte->value() + ( dSBImporte->value() * recargo ) ) );
}


/*!
    \fn FormAgregarRecibo::cambioImporte( double )
 */
void FormAgregarRecibo::cambioImporte( double )
{
  recalcular();
}


/*!
    \fn FormAgregarRecibo::guardar( bool imprimir )
	Guada los datos e imprime si es necesario
	@param imprimir Llama al metodo de impresion cuando termina
 */
void FormAgregarRecibo::guardar( bool imprimir )
{
 if( !RBCuentaCorriente->isChecked() && !RBContado->isChecked() )
 {
  QMessageBox::warning( this, "Error", "Por favor, seleccione una forma de pago" );
  return;
 }
 if( TETexto->contenido().isEmpty() )
 {
  if( !cBPagoMes->isChecked() )
  {
   QMessageBox::warning( this, "Error", "Por favor, ingrese un detalle" );
   return;
  }
 }
 if( dSBImporte->value() <= 0 )
 {
  QMessageBox::warning( this, "Error", "Por favor, ingrese un importe" );
  return;
 }
 if( cBPagoMes->isChecked() )
 {
	// Quiere ponerle texto? - lo busco en las preferencias
	if( preferencias::getInstancia()->value( "preferencias/recibos/tienetexto", false ).toBool() )
	{
		TETexto->setText( TETexto->contenido().append( preferencias::getInstancia()->value( "preferencias/recibos/textopagomes", "").toString().arg( CBMeses->currentText() ) ) );
	}
	else
	// Las preferencias no dicen nada, asi que pregunto
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question( this,
						"Confirmacion",
						"Desea que se agrege automaticamente el texto de pago del mes al recibo en el campo de texto?",
						QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
		if( reply == QMessageBox::Yes )
		{
			TETexto->setText( TETexto->contenido().append( preferencias::getInstancia()->value( "preferencias/recibos/textopagomes", "").toString().arg( CBMeses->currentText() ) ) );
		}
		else if( reply == QMessageBox::Cancel )
		{
			return;
		}

	}
 }
 MRecibo *modelo = new MRecibo( this );
 QSqlRecord rec = modelo->record();
 rec.remove( 0 );
 rec.setValue( "cliente", CBClientes->model()->data( CBClientes->model()->index( CBClientes->currentIndex(), 0 ), Qt::EditRole  ) );
 if( cBPagoMes->isChecked() )
 {
  rec.setValue( "num_mes", CBMeses->currentIndex() );
 }
 else
 {
  rec.setValue( "num_mes", -1 );
 }
 rec.setValue( "texto", TETexto->contenido() );
 rec.setValue( "precio", LETotal->text() );
 rec.setValue( "fecha_pago", dEFechaPago->date() );
 rec.setValue( "cuenta_corriente", RBCuentaCorriente->isChecked() );
 rec.setValue( "contado", RBContado->isChecked() );

 if( modelo->insertRecord( -1, rec ) )
 {
  QMessageBox::information( this, "Guardado", "Los datos han sido guardados correctamente" );
  visorRecibo *v = new visorRecibo();
  v->verRecibo( modelo->query().lastInsertId().toInt() );
  emit agregarVentana( v );
 /* if( imprimir )
  {
     v->imprimir();
  }*/
  this->hide();
  return;
 }
 else
 {
  qWarning( modelo->lastError().text().toLocal8Bit() );
  QMessageBox::critical( this, "Error", "Error al guardar los datos" );
  return;
 }
}


/*!
    \fn FormAgregarRecibo::guardarImprimir()
 */
void FormAgregarRecibo::guardarImprimir()
{
 guardar( true );
}
