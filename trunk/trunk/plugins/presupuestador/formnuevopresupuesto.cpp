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
#include "formnuevopresupuesto.h"
#include "presupuestador.h"
#include "visorresumen.h"
#include "eeditor.h"
#include "emcliente.h"
#include "emautos.h"

#include <QVBoxLayout>

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QMessageBox>
#include "ereporte.h"

FormNuevoPresupuesto::FormNuevoPresupuesto(QWidget* parent, Qt::WFlags fl)
: EVentana( parent, fl ), Ui::FormNuevoPresupuestoBase()
{
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	DTFecha->setDate( QDate::currentDate() );
	dSBTotal->setValue( 0 );

	QAction *ActGuardar= new QAction( "Guardar", this );
	ActGuardar->setIcon( QIcon( ":/imagenes/add.png" ) );
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( agregar() ) );

	QAction *ActCancelar = new QAction( "Cancelar", this );
	ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( close() ) );

	// Creo el editor
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


	CkBImprimir->setChecked( true );
	CkBEmail->setChecked( true );
	setWindowTitle( "Nuevo Presupuesto" );
	setObjectName( "NuevoPresupuesto" );
	setWindowIcon( QIcon( ":/imagenes/presupuesto.png" ) );
	addAction( ActGuardar );
	addAction( ActCancelar );
}

FormNuevoPresupuesto::~FormNuevoPresupuesto()
{
}

#include "mpresupuestos.h"
#include <QSqlRecord>
#include <QMessageBox>

/*!
    \fn FormNuevoPresupuesto::agregar()
 */
void FormNuevoPresupuesto::agregar()
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
 registro.setValue( "id_auto", CBAuto->model()->data( CBAuto->model()->index( CBAuto->currentIndex(), 0 ) ).toString() );
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
  mensaje.setText( QString( "El presupuesto se guardo correctamente con el numero %1.\n\n �Que desea hacer a continuacion?" ).arg( num_presupuesto ) );

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
   {
	EReporte *reporte = new EReporte( this );
	reporte->setArchivo( "plugins/presupuestos/informe-presupuestador.xml" );
	reporte->imprimir();
   }
   // Enviar x email
   case QMessageBox::ApplyRole:
   default:
    close();
    break;
  }
 }
}
