/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar  						   *
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
#include "formagregarpresupuesto.h"

#include "emcliente.h"
#include <QDate>
#include <QSqlError>
#include "eeditor.h"
#include "presupuesto.h"

FormAgregarPresupuesto::FormAgregarPresupuesto(QWidget* parent, Qt::WFlags fl)
: EVentana( parent, fl ), Ui::FormPresupuestoBase()
{
	// Inicializo el presupeusto!
	pre = new Presupuesto( this );
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	this->setObjectName( "FormAgregarPresupuesto" );
	this->setWindowTitle( "Agregar Presupuesto" );
	this->setWindowIcon( QIcon( ":/imagenes/nuevo.png" ) );

	connect( RBCliente, SIGNAL( toggled( bool ) ), CBCliente , SLOT( setEnabled( bool ) ) );
	connect( RBOtro   , SIGNAL( toggled( bool ) ), LEOtro    , SLOT( setEnabled( bool ) ) );
	connect( CkBTitulo, SIGNAL( toggled( bool ) ), LETitulo  , SLOT( setEnabled( bool ) ) );

	QAction *ActGuardar = new QAction( "Guardar", this );
	ActGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
	ActGuardar->setStatusTip( "Guarda el formulario de presupuesto actual y lo muestra ( Ctrl + g )" );
	ActGuardar->setShortcut( QKeySequence( "Ctrl+g" ) );
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );

	QAction *ActCancelar = new QAction( "Cancelar", this );
	ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	ActCancelar->setStatusTip( "Cancela los cambios realizados y cierra la ventana" );
	ActCancelar->setShortcut( QKeySequence( "Ctrl+c" ) );
	connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( cancelar() ) );

	QAction *ActGuardarImprimir = new QAction( "Guardar e Imprimir", this );
	ActGuardarImprimir->setIcon( QIcon( ":/imagenes/guardarimprimir.png" ) );
	ActGuardarImprimir->setStatusTip( "Guarda los datos y abre el dialogo de imprimir" );
	connect( ActGuardarImprimir, SIGNAL( triggered() ), this, SLOT( guardarImprimir() ) );

	QAction *ActImprimir = new QAction( "Imprimir", this );
	ActImprimir->setIcon( QIcon( ":/imagenes/imprimir.png" ) );
	ActImprimir->setStatusTip( "Imprime el presupuesto actual sin guardarlo" );
	connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

	// Agrego las acciones
	addAction( ActGuardar );
	addAction( ActGuardarImprimir );
	addAction( ActImprimir );
	addAction( ActCancelar );

	// Seteo la lista de clientes
	CBCliente->setModel( new EMCliente( CBCliente ) );
	CBCliente->setModelColumn( 1 );
	CBCliente->setCurrentIndex( -1 );

	// Pongo la fecha actual
	dEFecha->setDate( QDate::currentDate() );
}

FormAgregarPresupuesto::~FormAgregarPresupuesto()
{}

/*!
    \fn FormAgregarPresupuesto::cancelar()
	Elimina datos temporales y cierra el formulario
 */
void FormAgregarPresupuesto::cancelar()
{
    this->close();
}


#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include "mpresupuesto.h"
/*!
    \fn FormAgregarPresupuesto::guardar( bool cerrar )
 */
void FormAgregarPresupuesto::guardar( bool cerrar )
{
 // Verifico que esten todos los datos
 if( !RBCliente->isChecked() && !RBOtro->isChecked() )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, elija un cliente o destinatario" );
  return;
 }
 if( CkBTitulo->isChecked() && LETitulo->text().isEmpty() )
 {
	QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese el titulo personalizado" );
	return;
 }
 // Inicio la transacción
 QSqlDatabase::database().transaction();
 MPresupuesto *mod = new MPresupuesto( this, false );
 QSqlRecord reg = mod->record();
 // le pongo los valores a el registro
 reg.setValue( "titulo", LETitulo->text() );
 //reg.setValue( "contenido", editor->contenido() );
 reg.setValue( "fecha", dEFecha->date() );
 if( RBOtro->isChecked() )
 {
  reg.setValue( "destinatario", LEOtro->text() );
  reg.setValue( "id_cliente", -1 );
 }
 else
 {
  reg.setValue( "id_cliente", CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex() ,0 ) ).toInt() );
  reg.setValue( "destinatario", "" );
 }
 if( mod->insertRecord( -1, reg ) )
 {
  int id_presupuesto = -1;
  if( !QSqlDatabase::database().driver()->hasFeature( QSqlDriver::LastInsertId ) )
  { qDebug("Error, no hay last_id" ); QSqlDatabase::database().rollback(); return; }
  else
  {
	QVariant var = mod->query().lastInsertId();
	if( !var.isValid() )
	{
		qWarning( "Error al obtener el ultimo id" );
	}
	else
	{
		id_presupuesto = var.toInt();
	}
  }
  QSqlDatabase::database().commit();
  QMessageBox::information( this, "Correcto", "Datos Guardados correctamente" );
  return;
 }
 else
 {
  qWarning( qPrintable( "No se pudo guardar el registro: " + mod->lastError().text() ) );
  QSqlDatabase::database().rollback();
 }
 if( cerrar )
 {
  this->close();
 }
}


/*!
    \fn FormAgregarPresupuesto::imprimir()
 */
void FormAgregarPresupuesto::imprimir()
{
 qWarning( "No implementado todavia" );
}


/*!
    \fn FormAgregarPresupuesto::guardarImprimir()
 */
void FormAgregarPresupuesto::guardarImprimir()
{
 guardar( false );
 imprimir();
}


/*!
    \fn FormAgregarPresupuesto::guardar()
 */
void FormAgregarPresupuesto::guardar()
{
 guardar( true );
}
