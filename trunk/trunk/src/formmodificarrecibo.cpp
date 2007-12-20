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
#include "formmodificarrecibo.h"

#include <QSqlQueryModel>
#include <QMessageBox>
#include "gestotux.h"
#include <QSqlRecord>
#include <QSqlError>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QTextEdit>
#include <QLineEdit>
#include "mrecibo.h"
#include <QSqlQuery>

FormModificarRecibo::FormModificarRecibo( QWidget *parent )
 : EVentana( parent )
{
 setupUi( this );
 setObjectName( "Modificar Recibo" );

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setStatusTip( "Cierra la edicion del recibo actual y no guarda los cambios" );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

 ActGuardar = new QAction( "Guardar", this );
 ActGuardar->setStatusTip( "Guarda los datos del formulario" );
 ActGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
 connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );

 ActGuardarImprimir = new QAction( "Guardar e Imprimir" , this );
 ActGuardarImprimir->setStatusTip( "Guardar e imprimir el recibo actual" );
 ActGuardarImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
 connect( ActGuardarImprimir, SIGNAL( triggered() ), this, SLOT( guardarImprimir() ) );

 addAction( ActCerrar );
 addAction( ActGuardar );
 addAction( ActGuardarImprimir );

 setWindowTitle( "Modificar recibo"  );

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
}


FormModificarRecibo::~FormModificarRecibo()
{
}




/*!
    \fn FormModificarRecibo::cargarDatos( QModelIndex idDB )
 */
void FormModificarRecibo::cargarDatos( QModelIndex idDB, QSqlTableModel *modelo )
{
 indice = idDB;
 this->modelo = modelo;
 QSqlRecord registro = modelo->record( idDB.row() );

 TETexto->setText( registro.value( "texto" ).toString() );
   dEFechaPago->setDate( registro.value( "fecha_pago" ).toDate() );
   // tipo de pago
   if( registro.value( "cuenta_corriente" ).toBool() )
   {
    RBCuentaCorriente->setChecked( true );
   }
   else
   {
    RBContado->setChecked( true );
   }
   // mes
   if( registro.value( "mes" ).toInt() != -1 )
   {
    cBPagoMes->setCheckState( Qt::Checked );
    CBMeses->setCurrentIndex( registro.value( "mes" ).toInt() );
   }
   else
   {
    cBPagoMes->setCheckState( Qt::Unchecked );
   }
   // Recargo
   if( registro.value( "fecha_pago" ).toDate().day() > 13 || registro.value( "fecha_pago" ).toDate().day() <= 17 )
   {
    double importe = registro.value( "precio" ).toDouble() - ( registro.value( "precio" ).toDouble() * 0.05 );
    dSBImporte->setValue( importe );
    recargo = 0.05;
    cBRecargos->setCheckState( Qt::Checked );
    recalcular();
   }
   if( registro.value( "fecha_pago" ).toDate().day() >= 18 || registro.value( "fecha_pago" ).toDate().day() <= 31 )
   {
    double importe = registro.value( "precio" ).toDouble() - ( registro.value( "precio" ).toDouble() * 0.07 );
    dSBImporte->setValue( importe );
    recargo = 0.07;
    cBRecargos->setCheckState( Qt::Checked );
    recalcular();
   }
   // Cliente
   CBClientes->setCurrentIndex( CBClientes->model()->data( CBClientes->model()->index( registro.value( "cliente" ).toInt(), 0 ), Qt::EditRole  ).toInt() );
}


/*!
    \fn FormAgregarRecibo::nombre()
 */
QString FormModificarRecibo::nombre()
{
 return CBClientes->currentText();
}

void FormModificarRecibo::cambioEstadoPagoMes( int estado )
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

void FormModificarRecibo::cambioEstadoRecargos( int estado )
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
 recalcular();
}


/*!
    \fn FormAgregarRecibo::recalcular()
 */
void FormModificarRecibo::recalcular()
{
 LETotal->setText( QString().setNum( dSBImporte->value() + ( dSBImporte->value() * recargo ) ) );
}


/*!
    \fn FormAgregarRecibo::cambioImporte( double )
 */
void FormModificarRecibo::cambioImporte( double )
{
  recalcular();
}


/*!
    \fn FormAgregarRecibo::guardar()
 */
void FormModificarRecibo::guardar()
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
 modelo->setEditStrategy( QSqlTableModel::OnFieldChange );
 QSqlRecord rec = modelo->record( indice.row() );
 rec.remove( 0 );
 rec.setValue( "cliente", CBClientes->model()->data( CBClientes->model()->index( CBClientes->currentIndex(), 0 ), Qt::EditRole  ) );
 if( cBPagoMes->isChecked() )
 {
  rec.setValue( "num_mes", CBMeses->currentIndex() );
 }
 rec.setValue( "texto", TETexto->toPlainText() );
 rec.setValue( "precio", LETotal->text() );
 rec.setValue( "fecha_pago", dEFechaPago->date() );
 rec.setValue( "cuenta_corriente", RBCuentaCorriente->isChecked() );
 rec.setValue( "contado", RBContado->isChecked() );

 if( modelo->setRecord( indice.row(), rec ) )
 {
  QMessageBox::information( this, "Guardado", "Los datos han sido guardados correctamente" );
  gestotux::formCen()->cerrarActivo();
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
    \fn FormModificarRecibo::guardarImprimir()
 */
void FormModificarRecibo::guardarImprimir()
{
 guardar();
 gestotux::formCen()->imprimirActivo();
}
