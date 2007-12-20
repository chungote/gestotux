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
#include "preferencias.h"
#include <QSpinBox>
#include <QPrinter>
#include <QSqlRecord>
#include <QMessageBox>

FPrefRecibos::FPrefRecibos(QWidget *parent)
 : FormPrefHijo( parent ),Ui_FPrefRecibosBase()
{
 setupUi(this);


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
  preferencias *p = preferencias::getInstancia();
  p->inicio();
  p->beginGroup( "preferencias" );
  p->beginGroup( "recibos" );
  p->setValue( "tam", CBTam->currentIndex() );
  p->setValue( "orientacion", CBOrientacion->currentIndex() );
  p->setValue( "margen", dSBMargen->value() );
  p->endGroup();
  p->endGroup();
}


void FPrefRecibos::cargar()
{
  // Busco el ultimo numero de recibo
  QSqlQuery cola( "SELECT seq FROM sqlite_sequence WHERE name = 'recibos'" );
  if( cola.next() )
  {
   LNumeroActual->setText( cola.record().value( "seq" ).toString() );
   sBNuevoNumero->setMinimum( cola.record().value( "seq" ).toInt() );
   connect( PBSetear, SIGNAL( clicked() ), this, SLOT( setear() ) );
  }
  else
  {
    qWarning( "Error al obtener el numero actual de recibo" );
    LNumeroActual->setText( "Errrrrrrrr" );
    sBNuevoNumero->setEnabled( false );
    PBSetear->setEnabled( false );
  }

  preferencias *p = preferencias::getInstancia();
  p->inicio();
  p->beginGroup( "preferencias" );
  p->beginGroup( "recibos" );

  // Tama�o de las hojas
  CBTam->addItem( "A4", QPrinter::A4 );
  CBTam->setCurrentIndex( p->value( "tam", QPrinter::A4 ).toInt() );

  // Orientacion
  CBOrientacion->addItem( "Vertical", QPrinter::Portrait );
  CBOrientacion->addItem( "Horizontal", QPrinter::Landscape );
  CBOrientacion->setCurrentIndex( p->value( "orientacion", QPrinter::Landscape ).toInt() );

  // Margen
  dSBMargen->setValue( p->value( "margen", 15 ).toDouble() );
  dSBMargen->setMinimum( 0 );
}


/*!
    \fn FPrefRecibos::setear()
 */
void FPrefRecibos::setear()
{
 if( sBNuevoNumero->value() > LNumeroActual->text().toInt() )
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
 else
 {
  qWarning( "El numero a actualizar es menor o igual al numero actual" );
  return;
 }
}
