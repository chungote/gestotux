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
#include "eactguardar.h"
#include "eactcerrar.h"
#include "eregistroplugins.h"
#include "preferencias.h"
#include "../caja/mcajas.h"

FormAgregarGasto::FormAgregarGasto( QWidget* parent )
: EVentana( parent ), Ui::FormAgregarGastoBase()
{
        setupUi( this );
        setObjectName( "AgregarGasto" );
        setWindowTitle( "Agregar nuevo gasto" );

        this->addAction( new EActGuardar( this ) );
        this->addAction( new EActCerrar( this ) );

        /*modeloCombo = new QSqlQueryModel( this );
        modeloCombo->setQuery( "SELECT id, nombre FROM categoria WHERE tipo = '2'" );
        CBTipo->setModelColumn( 1 );
        CBTipo->setModel( modeloCombo );
        CBTipo->setModelColumn( 1 );
        CBTipo->setInsertPolicy( QComboBox::NoInsert );*/

        CWFecha->setSelectedDate( QDate::currentDate() );

        modeloEdit = new QSqlQueryModel( this );
        modeloEdit->setQuery( "SELECT DISTINCT descripcion FROM gastos" );
        CBDescripcion->setModel( modeloEdit );
        CBDescripcion->setEditable( true );

        if( ERegistroPlugins::getInstancia()->existePlugin( "caja" ) ) {
            CBCajas->setModel( new MCajas( this ) );
            CBCajas->setModelColumn( 1 );
            qobject_cast<QSqlTableModel *>(CBCajas->model())->select();
        } else {
            CkBSacarCaja->setVisible( false );
            CBCajas->setVisible( false );
        }
}

FormAgregarGasto::~FormAgregarGasto()
{
}

#include "../caja/mmovimientoscaja.h"
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
 /*else if( CBTipo->currentIndex() < 0 )
 {
  QMessageBox::warning( this, "Faltan Datos", "Por favor, ingrese una categoria para el gasto" );
  return;
 }*/
 else if( dSBCosto->value() <= 0 )
 {
  QMessageBox::warning( this, "Faltan Datos", "Por favor, ingrese una costo para este gasto" );
  return;
 }
 else
 {
  if( ERegistroPlugins::getInstancia()->existePlugin( "caja" ) ) {
      if( preferencias::getInstancia()->value("Preferencias/Caja/gastos-sinfondo").toBool() )
      {
          int id_caja = CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt();
          if( MCajas::saldo( id_caja ) < dSBCosto->value() ) {
              QMessageBox::warning( this, "Error", "El saldo en esta caja no es suficiente para ingresar este gasto. Modifique las preferencias para evitar este dialogo" );
              return;
          }
      }
  }
  MGasto *modelo = new MGasto( this );
  modelo->setEditStrategy( QSqlTableModel::OnManualSubmit );
  if ( modelo->agregarGasto( CBDescripcion->currentText(),
                                dSBCosto->value(),
                                CWFecha->selectedDate(),
                                CBTipo->model()->data( CBTipo->model()->index( CBTipo->currentIndex(), 0 ), Qt::EditRole ).toInt() ) == true )
  {
        if( modelo->submitAll() )
        {
             if( ERegistroPlugins::getInstancia()->existePlugin( "caja" ) ) {
                 MMovimientosCaja *m = new MMovimientosCaja();
                 int id_caja = CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt();
                 if( !m->agregarMovimiento( id_caja, CBDescripcion->currentText(), QString(), 0.0, dSBCosto->value() ) ) {
                     QMessageBox::information( this, "Error", "El gasto se guardo correctamente, pero no se pudo registrar la operacion en la cuenta de caja" );
                     this->close();
                     return;
                 }
             }
            QMessageBox::information( this, "Correcto", "El gasto se han agregado correctamente" );
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
