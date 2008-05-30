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

FormModificarPresupuesto::FormModificarPresupuesto(QWidget* parent, Qt::WFlags fl)
: EVentana( parent ), Ui::FormNuevoPresupuestoBase()
{
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	setWindowTitle( "Modificar Presupuesto" );

	QAction *ActGuardar= new QAction( "Guardar", this );
	ActGuardar->setIcon( QIcon( ":/imagenes/add.png" ) );
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( agregar() ) );

	QAction *ActCancelar = new QAction( "Cancelar", this );
	ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( close() ) );

	addAction( ActGuardar );
	addAction( ActCancelar );
}

FormModificarPresupuesto::~FormModificarPresupuesto()
{
}


/*!
    \fn FormModificarPresupuesto::setId( int idDB )
 */
void FormModificarPresupuesto::setId( int idDB )
{
 QSqlQuery cola( QString( "SELECT destinatario, fecha, total, contenido FROM presupuestos WHERE id = %1" ).arg( idDB ) );
 if( cola.next() )
 {
  LEDestinatario->setText( cola.record().value( "destinatario" ).toString() );
  dSBTotal->setValue( cola.record().value( "total" ).toDouble() );
  DEFecha->setDate( cola.record().value( "fecha" ).toDate() );
  TEContenido->document()->setHtml( cola.record().value( "contenido" ).toString() );
  this->idDB = idDB;
 }
}


/*!
    \fn FormModificarPresupuesto::guardar()
 */
void FormModificarPresupuesto::guardar()
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

 QSqlQuery cola;
 cola.prepare( QString( "UPDATE presupuestos SET destinatario = ?, total = ?, fecha = ?, contenido = ? WHERE id = '%1'" ).arg( idDB ) );
 cola.bindValue( 0, LEDestinatario->text() );
 cola.bindValue( 1, dSBTotal->value() );
 cola.bindValue( 2, DEFecha->date().toString( Qt::ISODate ) );
 cola.bindValue( 3, TEContenido->document()->toHtml() );
 if( cola.exec() )
 {
  close();
 }
 else
 {
  qCritical( "No se pudo actualizar el registro" );
  qCritical( cola.lastError().text().toLocal8Bit() );
  qCritical( cola.executedQuery().toLocal8Bit() );
 }
}
