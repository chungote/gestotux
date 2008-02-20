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

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QMessageBox>

FormNuevoPresupuesto::FormNuevoPresupuesto(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::FormNuevoPresupuestoBase()
{
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	DEFecha->setDate( QDate::currentDate() );
	dSBTotal->setValue( 0 );

	QAction *ActGuardar= new QAction( "Guardar", this );
	ActGuardar->setIcon( QIcon( ":/imagenes/add.png" ) );
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( agregar() ) );

	QAction *ActCancelar = new QAction( "Cancelar", this );
	ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( close() ) );

	setWindowTitle( "Nuevo Presupuesto" );
	addAction( ActGuardar );
	addAction( ActCancelar );
}

FormNuevoPresupuesto::~FormNuevoPresupuesto()
{
}


/*!
    \fn FormNuevoPresupuesto::agregar()
 */
void FormNuevoPresupuesto::agregar()
{
 if( LEDestinatario->text().isEmpty() )
 {
 QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un destinatario al cual realizar el presupuesto" );
  return;
 }
 //qDebug( TEContenido->toPlainText().toLocal8Bit() );
 if( TEContenido->toPlainText().isEmpty() )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un detalle de presupuesto" );
  return;
 }
 if( dSBTotal->value() <= 0 )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un monto a presupuestar" );
  return;
 }
 //Agrego el registro
 QSqlTableModel *modelo = new QSqlTableModel( this );
 modelo->setTable( "presupuestos" );
 QSqlRecord registro = modelo->record();
 registro.setValue( "total", dSBTotal->value() );
 registro.setValue( "destinatario", LEDestinatario->text() );
 registro.setValue( "fecha", DEFecha->date().toString( Qt::ISODate ) );
 registro.setValue( "contenido", TEContenido->toHtml() );
 modelo->insertRecord( -1, registro );
 QSqlQuery cola( "SELECT seq FROM sqlite_sequence WHERE name = 'presupuestos'" );
 if( cola.next() )
 {
  int id = cola.record().value(0).toInt();
  visorResumen *v = new visorResumen( this );
  v->set_registro( id );
  presupuestador::tabs()->setCurrentWidget( presupuestador::tabs()->widget( presupuestador::tabs()->addWidget( v ) ) );
  this->close();
 }
 else
 {
  qDebug( "Error al ejecutar la cola" );
 }
}
