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

#include <QStyleFactory>
#include <QComboBox>
#include <QApplication>
#include <QTimer>
#include <QColor>
#include <QColorDialog>
#include "preferencias.h"
#include "fprefgeneral.h"

FPrefGeneral::FPrefGeneral( QWidget* parent )
: FormPrefHijo( parent ), Ui::FPrefGeneralBase()
{
	setupUi(this);
 	this->setAttribute( Qt::WA_DeleteOnClose );
	CBEstilo->insertItems( -1, QStyleFactory::keys() );
	connect( ChBBarraProgreso, SIGNAL( stateChanged( int ) ), this, SLOT( cambioEstadoBarra( int ) ) );
	PBMuestra->setStyleSheet( "QProgressBar:horizontal { border: 1px solid gray; border-radius: 6px; background: white; padding: 0px; text-align: center; text-padding: 4px; text-weight: bold; } QProgressBar::chunk:horizontal { background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 blue, stop: 1 cyan); }" );
	QTimer *tiempo = new QTimer( this );
	tiempo->setInterval( 900 );
	connect( tiempo, SIGNAL( timeout() ), this, SLOT( avanzarBarra() ) );
	tiempo->start();
}

FPrefGeneral::~FPrefGeneral()
{
}



/*!
    \fn FPrefGeneral::cargar()
 */
void FPrefGeneral::cargar()
{
 preferencias *p = preferencias::getInstancia();
 p->inicio();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "General" );
 ChBMaximizado->setChecked( p->value( "maximizado" , false ).toBool() );
 CBEstilo->setCurrentIndex( p->value( "estilo-int", 5 ).toInt() );
 ChBSplash->setChecked( p->value( "splash", true ).toBool() );
 ChBIconoBandeja->setChecked( p->value( "icono_bandeja", false ).toBool() );
 ChBBarraProgreso->setChecked( p->value( "barra_personalizada", false ).toBool() );
 PBMuestra->setEnabled( p->value( "barra_personalizada", false ).toBool() );
 p->endGroup();
 p->endGroup();
}


/*!
    \fn FPrefGeneral::guardar()
 */
void FPrefGeneral::guardar()
{
 preferencias *p = preferencias::getInstancia();
 p->inicio();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "General" );
 p->setValue( "maximizado", ChBMaximizado->isChecked() );
 p->setValue( "estilo", CBEstilo->currentText() );
 p->setValue( "estilo-int", CBEstilo->currentIndex() );
 p->setValue( "splash", ChBSplash->isChecked() );
 p->setValue( "icono_bandeja", ChBIconoBandeja->isChecked() );
 p->setValue( "barra_personalizada", ChBBarraProgreso->isChecked() );
 p->endGroup();
 p->endGroup();
}


/*!
    \fn FPrefGeneral::aplicar()
 */
void FPrefGeneral::aplicar()
{
  QApplication::setStyle( QStyleFactory::create( CBEstilo->currentText() ) );
  if( ChBBarraProgreso->isChecked() )
  {
   QString estilo = qApp->styleSheet();
   qApp->setStyleSheet( estilo.append( "QProgressBar:horizontal { border: 1px solid gray; border-radius: 6px; background: white; padding: 0px; text-align: center; text-padding: 4px; text-weight: bold; } QProgressBar::chunk:horizontal { background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 blue, stop: 1 cyan); }" ) );
  }
}


/*!
    \fn FPrefGeneral::cambioEstadoBarra( int estado )
 */
void FPrefGeneral::cambioEstadoBarra( int estado )
{
 switch( estado )
 {
   case Qt::Unchecked:
  {
   PBMuestra->setEnabled( false );
   break;
  }
  case Qt::Checked:
  {
   PBMuestra->setEnabled( true );
   break;
  }
 }
}


/*!
    \fn FPrefGeneral::avanzarBarra()
 */
void FPrefGeneral::avanzarBarra()
{
 if( PBMuestra->value() == 100 )
 {
  PBMuestra->setValue( 0 );
 }
 else
 {
  PBMuestra->setValue( PBMuestra->value() + 1 );
 }
}

