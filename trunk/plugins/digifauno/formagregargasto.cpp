/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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
#include "formagregargasto.h"

#include <QPushButton>
#include <QComboBox>
#include <QCalendarWidget>
#include <QDate>
#include <QMessageBox>
#include <QSqlError>

#include "mgasto.h"

FormAgregarGasto::FormAgregarGasto( QWidget* parent )
: EVentana( parent ), Ui::FormAgregarGastoBase()
{
	setupUi( this );
	nombre_ventana = "AgregarGasto";
	setNombreVentana( "Agregar nuevo gasto" );

        PBGuardar->setText( "&Guardar" );
	PBGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
	PBGuardar->setShortcut( QKeySequence( "Crtl+g" ) );
	PBCerrar->setText( "Cer&rar" );
	PBCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	PBCerrar->setShortcut( QKeySequence( "Crtl+r" ) );

	connect( PBCerrar , SIGNAL( clicked() ), this, SLOT( close()   ) );
 	connect( PBGuardar, SIGNAL( clicked() ), this, SLOT( guardar() ) );

	QSqlQueryModel *modeloCombo = new QSqlQueryModel( this );
	modeloCombo->setQuery( "SELECT id, nombre FROM categoria WHERE tipo = '2'" );
	CBTipo->setModelColumn( 1 );
	CBTipo->setModel( modeloCombo );
	CBTipo->setModelColumn( 1 );
	CBTipo->setInsertPolicy( QComboBox::NoInsert );

	CWFecha->setSelectedDate( QDate::currentDate() );

	QSqlQueryModel *modeloEdit = new QSqlQueryModel( this );
	modeloEdit->setQuery( "SELECT DISTINCT descripcion FROM gastos" );
	CBDescripcion->setModel( modeloEdit );
	CBDescripcion->setEditable( true );
}

FormAgregarGasto::~FormAgregarGasto()
{
}



/*!
    \fn FormAgregarGasto::guardar()
 */
void FormAgregarGasto::guardar()
{
 if( CBDescripcion->currentText().isEmpty() )
 {
  QMessageBox::warning( this, "Faltan Datos", "Por favor, ingrese una descripcion para el gasto" );
  return;
 }
 else if( CBTipo->currentIndex() < 0 )
 {
  QMessageBox::warning( this, "Faltan Datos", "Por favor, ingrese una categoria para el gasto" );
  return;
 }
 else if( dSBCosto->value() <= 0 )
 {
  QMessageBox::warning( this, "Faltan Datos", "Por favor, ingrese una costo para este gasto" );
  return;
 }
 else
 {
  MGasto *modelo = new MGasto( this );
  modelo->setEditStrategy( QSqlTableModel::OnManualSubmit );
  if ( modelo->agregarGasto( CBDescripcion->currentText(),
				dSBCosto->value(),
				CWFecha->selectedDate(),
				CBTipo->model()->data( CBTipo->model()->index( CBTipo->currentIndex(), 0 ), Qt::EditRole ).toInt() ) == true )
  {
	if( modelo->submitAll() )
	{
		QMessageBox::information( this, "Correcto", "El gasto se han agregado correctamente" );
		delete modelo;
		this->close();
		return;
	}
	else
	{
		QMessageBox::information( this, "Error de base de datos", "Los datos del gasto no se han agregado" );
		qDebug( "Error de submit" );
		qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modelo->lastError().type() ).arg( modelo->lastError().number() ).arg( modelo->lastError().text() ).toLocal8Bit() );
		return;
	}
  }
  else
  {
   QMessageBox::critical( this, "Error", "Hubo un error al intentar agregar el gasto. No se guardaron datos." );
   return;
  }
 }
}
