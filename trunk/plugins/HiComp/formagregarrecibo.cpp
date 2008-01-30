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
#include "gestotux.h"
// #include "mrecibo.h"
//#include "visorrecibo.h"

#include <QLocale>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlQuery>
#include <QRadioButton>
#include <QSqlError>
#include <QDate>

FormAgregarRecibo::FormAgregarRecibo(QWidget *parent)
 : EVentana(parent), Ui_FormAgregarReciboBase()
{
 setupUi( this );
 setObjectName( "Nuevo Recibo" );
 setWindowTitle( "Nuevo Recibo" );

 recargo = 0;

 // Cargo los meses
 QLocale locale;
 for( int i = 1; i<=12; i++ )
 {
  CBMeses->addItem( locale.monthName( i, QLocale::LongFormat ) );
 }

 QSqlQueryModel *mcli = new QSqlQueryModel( this );
 mcli->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );
 CBClientes->setModel( mcli );
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
 connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );

 ActCancelar = new QAction( "Cancelar", this );
 ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 ActCancelar->setStatusTip( "Cancela los datos ingresados y no genera un recibo" );
 connect( ActCancelar, SIGNAL( triggered() ), gestotux::formCen(), SLOT( cerrarActivo() ) );

 ActGuardarImprimir = new QAction( "Guardar e Imprimir", this );
 ActGuardarImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
 ActGuardarImprimir->setStatusTip( "Guarda los datos e imprime directamente el recibo" );
 connect( ActGuardarImprimir, SIGNAL( triggered() ), this, SLOT( guardarImprimir() ) );

 addAction( ActCancelar );
 addAction( ActGuardar );
 addAction( ActGuardarImprimir );
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
    \fn FormAgregarRecibo::guardar()
 */
void FormAgregarRecibo::guardar()
{
 if( !RBCuentaCorriente->isChecked() && !RBContado->isChecked() )
 {
  QMessageBox::warning( this, "Error", "Por favor, seleccione una forma de pago" );
  return;
 }
 if( TETexto->toPlainText().isEmpty() )
 {
  QMessageBox::warning( this, "Error", "Por favor, ingrese un detalle" );
  return;
 }
 if( dSBImporte->value() <= 0 )
 {
  QMessageBox::warning( this, "Error", "Por favor, ingrese un importe" );
  return;
 }
/* MRecibo *modelo = new MRecibo();
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
 rec.setValue( "texto", TETexto->toPlainText() );
 rec.setValue( "precio", LETotal->text() );
 rec.setValue( "fecha_pago", dEFechaPago->date() );
 rec.setValue( "cuenta_corriente", RBCuentaCorriente->isChecked() );
 rec.setValue( "contado", RBContado->isChecked() );

 if( modelo->insertRecord( -1, rec ) )
 {
  QMessageBox::information( this, "Guardado", "Los datos han sido guardados correctamente" );
  gestotux::formCen()->cerrarActivo();
  QSqlQuery cola( "SELECT seq FROM sqlite_sequence WHERE name = 'recibos'" );
  if( cola.next() )
  {
//    gestotux::formCen()->agregarRecibo( cola.record().value( "seq" ).toInt() );
  }
  return;
 }
 else
 {
  qWarning( modelo->lastError().text().toLocal8Bit() );
  QMessageBox::critical( this, "Error", "Error al guardar los datos" );
  return;
 }*/
}


/*!
    \fn FormAgregarRecibo::guardarImprimir()
 */
void FormAgregarRecibo::guardarImprimir()
{
 guardar();
//  gestotux::formCen()->imprimirActivo();
}
