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
#include "fprefrecibos.h"

#include <QSqlQuery>
#include <QDoubleSpinBox>
#include "hicomp.h"
#include <QSettings>
#include <QSpinBox>
#include <QPrinter>
#include <QSqlRecord>
#include <QMessageBox>
#include "preferencias.h"

FPrefRecibos::FPrefRecibos(QWidget *parent)
 : EVentana( parent ), Ui_FPrefRecibosBase()
{
 setupUi(this);
 this->setAttribute( Qt::WA_DeleteOnClose );
 setWindowTitle( "Recibos" );
 setWindowIcon( QIcon( ":/imagenes/recibo.png" ) );
}

FPrefRecibos::~FPrefRecibos()
{
}


void FPrefRecibos::aplicar()
{
 return;
}


void FPrefRecibos::guardar()
{
  QSettings *p = preferencias::getInstancia();
  p->setValue( "preferencias/recibos/margen", dSBMargen->value() );
  p->setValue( "preferencias/recibos/tienetexto", GBPagoMes->isChecked() );
  p->setValue( "preferencias/recibos/textopagomes", LETextoPagoMes->text() );
}


void FPrefRecibos::cargar()
{
  // Busco el ultimo numero de recibo
  QSqlQuery *cola = new QSqlQuery();
  if( QSqlDatabase::database().driverName() == "QSQLITE" )
  {
	cola->exec( "SELECT seq FROM sqlite_sequence WHERE name = 'recibos'" );
	if( cola->next() )
	{
		LNumeroActual->setText( cola->record().value( "seq" ).toString() );
		sBNuevoNumero->setMinimum( cola->record().value( "seq" ).toInt() );
		connect( PBSetear, SIGNAL( clicked() ), this, SLOT( setear() ) );
	}
	else
	{
		qWarning( "Error al obtener el numero actual de recibo" );
		LNumeroActual->setText( "Errrrrrrrr" );
		sBNuevoNumero->setEnabled( false );
		PBSetear->setEnabled( false );
	}
  }
  else if( QSqlDatabase::database().driverName() == "QMYSQL" )
  {
	cola->exec( "SELECT seq_in_index FROM INFORMATION_SCHEMA.STATISTICS WHERE table_name = 'recibos'" );
	if( cola->next() )
	{
		LNumeroActual->setText( cola->record().value(0).toString() );
		sBNuevoNumero->setMinimum( cola->record().value(0).toInt() );
		connect( PBSetear, SIGNAL( clicked() ), this, SLOT( setear() ) );
	}
	else
	{
		qWarning( "Error al obtener el numero actual de recibo" );
		LNumeroActual->setText( "Errrrrrrrr" );
		sBNuevoNumero->setEnabled( false );
		PBSetear->setEnabled( false );
	}
  }
  delete cola;

  QSettings *p = preferencias::getInstancia();
  // Margen
  dSBMargen->setValue( p->value( "preferencias/recibos/margen", 15 ).toDouble() );
  dSBMargen->setMinimum( 0 );

  // Texto del recibo
  GBPagoMes->setChecked( p->value( "preferencias/recibos/tienetexto", true ).toBool() );
  LETextoPagoMes->setText( p->value( "preferencias/recibos/textopagomes", "Servicio de Internet del mes de %1" ).toString() );
}


/*!
    \fn FPrefRecibos::setear()
 */
void FPrefRecibos::setear()
{
 if( sBNuevoNumero->value() > LNumeroActual->text().toInt() )
 {
  if( QSqlDatabase::database().driverName() == "QSQLITE" )
  {
	QSqlQuery cola( QString( "UPDATE sqlite_sequence SET seq = '%1' WHERE name = 'recibos'" ).arg( sBNuevoNumero->value() ) );
	if( cola.isActive() )
	{
		QMessageBox::information( this, "Hecho", "El numero de recibo ha sido actualizado" );
		QSqlQuery cola( "SELECT seq FROM sqlite_sequence WHERE name = 'recibos'" );
		if( cola.next() )
		{
			LNumeroActual->setText( cola.record().value( "seq" ).toString() );
			sBNuevoNumero->setMinimum( cola.record().value( "seq" ).toInt() );
		}
		else
		{
			qWarning( "Error al obtener el numero actual de recibo" );
			LNumeroActual->setText( "Errrrrrrrr" );
			sBNuevoNumero->setEnabled( false );
			PBSetear->setEnabled( false );
		}
		return;
	}
	else
	{
		QMessageBox::warning( this, "Error", "Hubo un error al intentar actualizar el numero de recibo. No se modifico." );
		return;
	}
   }
   else if( QSqlDatabase::database().driverName() == "QMYSQL" )
   {
	QSqlQuery cola( QString( "alter table recibos auto_increment=%1" ).arg( sBNuevoNumero->value() ) );
	if( cola.isActive() )
	{
		QMessageBox::information( this, "Hecho", "El numero de recibo ha sido actualizado" );
		QSqlQuery cola( "SELECT seq_in_index FROM INFORMATION_SCHEMA.STATISTICS WHERE table_name = 'recibos'" );
		if( cola.next() )
		{
			LNumeroActual->setText( cola.record().value( 0).toString() );
			sBNuevoNumero->setMinimum( cola.record().value(0).toInt() );
		}
		else
		{
			qWarning( "Error al obtener el numero actual de recibo" );
			LNumeroActual->setText( "Errrrrrrrr" );
			sBNuevoNumero->setEnabled( false );
			PBSetear->setEnabled( false );
		}
		return;
	}
	else
	{
		QMessageBox::warning( this, "Error", "Hubo un error al intentar actualizar el numero de recibo. No se modifico." );
		return;
	}
   }
 }
 else
 {
  qWarning( "El numero a actualizar es menor o igual al numero actual" );
  return;
 }
}
