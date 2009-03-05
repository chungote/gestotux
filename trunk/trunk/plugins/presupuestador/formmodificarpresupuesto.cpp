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

FormModificarPresupuesto::FormModificarPresupuesto( int id_presupuesto, QWidget* parent, Qt::WFlags fl)
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
	connect( CBCliente, SIGNAL( currentIndexChanged( int ) ), CBCliente->model(), SLOT( filtrarPorCliente( int ) ) );
	// Cargo los Autos

	CBAuto->setModel( new EMAutos( CBAuto ) );
	CBAuto->setModelColumn( 1 );
	CBAuto->setCurrentIndex( -1 );

	setId( id_presupuesto );
}

FormModificarPresupuesto::~FormModificarPresupuesto()
{
}


/*!
    \fn FormModificarPresupuesto::setId( int idDB )
 */
void FormModificarPresupuesto::setId( int idDB )
{
 QSqlQuery cola( QString( "SELECT * FROM presupuesto WHERE id_presupuesto = %1" ).arg( idDB ) );
 if( cola.next() )
 {
  dSBTotal->setValue( cola.record().value( "total" ).toDouble() );
  DTFecha->setDate( cola.record().value( "fecha" ).toDate() );
  editor->setHtml( cola.record().value( "contenido" ).toString() );
//  CBAuto->setCurrentText( cola.record().value( "id_auto" ).toString() );
  /// @todo Agregar reconociemiento de cliente x auto
  CkBImprimir->setChecked( cola.record().value( "imprimir" ).toBool() );
  CkBEmail->setChecked( cola.record().value( "email" ).toBool() );
  TBMemo->setText( cola.record().value( "memo" ).toString() );
  SBKilometraje->setValue( cola.record().value( "kilometraje" ).toDouble() );
  this->idDB = idDB;
 }
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
 //qDebug( TEContenido->toPlainText().toLocal8Bit() );
 if( editor->contenido( Qt::AutoText ).isEmpty() )
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
 MPresupuestos *presupuesto = new MPresupuestos( this );
 QSqlRecord registro = presupuesto->record();
 registro.remove( 0 );
 registro.setValue( "fecha", DTFecha->date() );
 registro.setValue( "titulo", LETitulo->text() );
 registro.setValue( "id_auto", "patente" );
 registro.setValue( "kilometraje", SBKilometraje->value() );
 registro.setValue( "contenido", editor->contenido() );
 registro.setValue( "memo", TBMemo->document()->toHtml() );
 registro.setValue( "creado", QDate::currentDate() );
 registro.setValue( "imprimir", CkBImprimir->isChecked() );
 registro.setValue( "email", CkBEmail->isChecked() );
 if( presupuesto->insertRecord( -1, registro ) )
 {
  // Registro agregado correctamente
  // obtengo el numero de presupuesto
  int num_presupuesto = presupuesto->query().lastInsertId().toInt();
  QMessageBox mensaje;
  mensaje.setText( QString( "El presupuesto se guardo correctamente con el numero %1.\n\n ¿Que desea hacer a continuacion?" ).arg( num_presupuesto ) );

  QPushButton *Bimprimir = mensaje.addButton( tr( "Imprimir" ), QMessageBox::ResetRole );
  Bimprimir->setIcon( QIcon( ":/imagenes/imprimir.png" ) );

  QPushButton *Bemail = mensaje.addButton( tr( "Enviar por email" ), QMessageBox::ApplyRole );
  Bemail->setIcon( QIcon( ":/imagenes/email.png" ) );

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
