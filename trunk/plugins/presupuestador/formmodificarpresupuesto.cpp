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

#include <QSqlQuery>
#include "formmodificarpresupuesto.h"
#include <QSqlRecord>
#include <QMessageBox>
#include <QDate>
#include <QSqlError>

#include "eactcerrar.h"
#include "eactguardar.h"
#include "mpresupuestos.h"
#include "emcliente.h"
#include "emautos.h"

FormModificarPresupuesto::FormModificarPresupuesto( QWidget* parent, Qt::WFlags fl)
: EVentana( parent, fl ), Ui::FormNuevoPresupuestoBase()
{
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	setObjectName( "modificarPresupuesto" );
	setWindowTitle( "Modificar Presupuesto" );
	setWindowIcon( QIcon( ":/imagenes/presupuesto.png" ) );

	addAction( new EActGuardar( this ) );
	addAction( new EActCerrar( this ) );

	editor = new EEditor( this );
	QVBoxLayout *v = new QVBoxLayout( GBContenido );
	v->addWidget( editor );

	// Cargo los Clientes
	CBCliente->setModel( new EMCliente( CBCliente ) );
	CBCliente->setModelColumn( 1 );
	CBCliente->setCurrentIndex( -1 );

	// Cargo los Autos
	CBAuto->setModel( new EMAutos( CBAuto ) );
	CBAuto->setModelColumn( 1 );
	CBAuto->setCurrentIndex( -1 );

	connect( CBCliente, SIGNAL( currentIndexChanged( int ) ), qobject_cast<EMAutos *>(CBAuto->model()), SLOT( filtrarPorCliente( int ) ) );
}

FormModificarPresupuesto::~FormModificarPresupuesto()
{
}


/*!
    \fn FormModificarPresupuesto::setId( int idDB )
 */
void FormModificarPresupuesto::setId( int row )
{
  if( row < 0 )
  { qWarning( "Indice Invalido" ); }
  qDebug( qPrintable( "Cargando fila: " + QString::number( row ) ) );
  QSqlRecord registro = modelo->record( row );
  if( !registro.isEmpty() <= 0 )
  { qWarning( "Sin registros" ); return; }
  dSBTotal->setValue( registro.value( "total" ).toDouble() );
  DTFecha->setDate( registro.value( "fecha" ).toDate() );
  editor->setHtml( registro.value( "contenido" ).toString() );
//  CBAuto->setCurrentIndex( CBAuto->model()->index( registro.value( "id_auto" ).toString(), 0 ).toInt() );
  //Busco el auto
  QSqlQuery cola( QString( "SELECT id FROM clientes, autos WHERE patente = %1 AND autos.id_dueno = clientes.id" ).arg( registro.value( "id_auto" ).toInt() ) );
  if( cola.next() )
  { CBCliente->setCurrentIndex( cola.record().value(0).toInt() ); }
  else
  { CBCliente->setCurrentIndex( -1 ); qDebug( qPrintable( "Error al conseguir el cliente" + cola.lastError().text() ) ); }
  CkBImprimir->setChecked( registro.value( "imprimir" ).toBool() );
  CkBEmail->setChecked( registro.value( "email" ).toBool() );
  if( registro.value( "memo" ).isNull() )
  { GBMemo->setChecked( false ); }
  else
  { TBMemo->setText( registro.value( "memo" ).toString() );  GBMemo->setChecked( true ); }
  SBKilometraje->setValue( registro.value( "kilometraje" ).toDouble() );
  indice = row;
}


/*!
    \fn FormModificarPresupuesto::guardar()
 */
void FormModificarPresupuesto::guardar()
{
 if( CkBTitulo->isChecked() && LETitulo->text().isEmpty() )
 {
 QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un titulo para el presupuesto o desseleccione la opcion de titulo personalizado" );
  return;
 }
 if( editor->contenido( Qt::PlainText ).isEmpty() )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un detalle de presupuesto" );
  return;
 }
 if( dSBTotal->value() <= 0 )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un monto a presupuestar" );
  return;
 }
 if( SBKilometraje->value() <= 0 )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un kilometraaje valido" );
  return;
 }
 // un cliente y un auto tienen que estar seleccionados
 if( CBCliente->currentText().isEmpty() )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un cliente valido" );
  return;
 }
 if( CBAuto->currentText().isEmpty() )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un auto valido" );
  return;
 }
 //Agrego el registro
 QSqlRecord registro = modelo->record( indice );
 registro.remove( 0 );
 registro.setValue( "fecha", DTFecha->date() );
 registro.setValue( "titulo", LETitulo->text() );
 registro.setValue( "id_auto", CBAuto->model()->data( CBAuto->model()->index( CBAuto->currentIndex(), 0 ) ).toString()  );
 registro.setValue( "kilometraje", SBKilometraje->value() );
 registro.setValue( "contenido", editor->contenido() );
 registro.setValue( "memo", TBMemo->document()->toHtml() );
 registro.setValue( "creado", QDateTime::currentDateTime() );
 registro.setValue( "imprimir", CkBImprimir->isChecked() );
 registro.setValue( "email", CkBEmail->isChecked() );
 if( modelo->setRecord( indice, registro ) )
 {
  // Registro agregado correctamente
  // obtengo el numero de presupuesto
  int num_presupuesto = modelo->query().lastInsertId().toInt();
  QMessageBox mensaje;
  mensaje.setText( QString( "El presupuesto se guardo correctamente con el numero %1.\n\n ¿Que desea hacer a continuacion?" ).arg( num_presupuesto ) );

  QPushButton *Bimprimir = mensaje.addButton( tr( "Imprimir" ), QMessageBox::ResetRole );
  Bimprimir->setIcon( QIcon( ":/imagenes/imprimir.png" ) );

  /*QPushButton *Bemail = mensaje.addButton( tr( "Enviar por email" ), QMessageBox::ApplyRole );
  Bemail->setIcon( QIcon( ":/imagenes/email.png" ) );*/

  mensaje.addButton( tr( "No hacer nada" ), QMessageBox::AcceptRole );

  int ret = mensaje.exec();
  switch( ret )
  {
   // Imprimir
   case QMessageBox::Reset:
   // Enviar x email
   case QMessageBox::ApplyRole:
   default:
    close();
    break;
  }
 }
 else
 {
  qWarning( "Error" );
 }

}


/*!
    \fn FormModificarPresupuesto::setModel( QSqlTableModel *modelo )
 */
void FormModificarPresupuesto::setModel( QSqlTableModel *modelo )
{
 this->modelo = modelo;
}
