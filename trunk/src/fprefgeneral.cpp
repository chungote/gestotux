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
#include <QDir>
#include "preferencias.h"
#include "fprefgeneral.h"

FPrefGeneral::FPrefGeneral( QWidget* parent )
: EVentana( parent ), Ui::FPrefGeneralBase()
{
	setupUi(this);
 	this->setAttribute( Qt::WA_DeleteOnClose );
	CBEstilo->insertItems( -1, QStyleFactory::keys() );
	connect( ChBBarraProgreso, SIGNAL( stateChanged( int ) ), this, SLOT( cambioEstadoBarra( int ) ) );
	PBMuestra->setStyleSheet( "QProgressBar:horizontal { border: 1px solid gray; border-radius: 6px; background: white; padding: 0px; text-align: center; } QProgressBar::chunk:horizontal { background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 blue, stop: 1 cyan); }" );
	QTimer *tiempo = new QTimer( this );
	tiempo->setInterval( 900 );
	connect( tiempo, SIGNAL( timeout() ), this, SLOT( avanzarBarra() ) );
	tiempo->start();
	CBSobreEstilo->setEnabled( CkBSobreEstilo->isChecked() );
	// Busco los estilos disponibles
	QDir dir( QCoreApplication::applicationDirPath() );
	dir.cd( "estilos" );
	if( dir.entryList( QDir::Dirs | QDir::NoDotAndDotDot ).isEmpty() )
	{
		CkBSobreEstilo->setEnabled(false);
		CBSobreEstilo->setEnabled(false);
	}
	else
	{
		// inserto los directorios de estilo
		CBSobreEstilo->insertItems( -1, dir.entryList( QDir::Dirs | QDir::NoDotAndDotDot ) );
		// conecto el slot que realiza el cambio
		connect( CBSobreEstilo, SIGNAL( currentIndexChanged( const QString & ) ), this, SLOT( cambioSobreEstilo( const QString & ) ) );
		// conecto el slot para deshacer los cambios si se dechequea la casilla
		connect( CkBSobreEstilo, SIGNAL( toggled( bool ) ), this, SLOT( cambioSobreEstilo( bool ) ) );
	}
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
 CkBSobreEstilo->setChecked( p->value( "sobreestilo", false ).toBool() );
 CBSobreEstilo->setCurrentIndex( p->value( "sobreestilonombreint", 0 ).toInt() );
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
 p->setValue( "sobreestilo", CkBSobreEstilo->isChecked() );
 p->setValue( "sobreestilonombre", CBSobreEstilo->currentText() );
 p->setValue( "sobreestiloint", CBSobreEstilo->currentIndex() );
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



/*!
    \fn FPrefGeneral::cambioSobreEstilo( bool estado )
 */
void FPrefGeneral::cambioSobreEstilo( bool estado )
{
 // el combobox se deshabilita solo asique limpio el estilo que haya
 if( estado )
 {
  cambioSobreEstilo( CBSobreEstilo->currentText() );
 }
 else
 {
   qApp->setStyleSheet( QString() );
 }
}


/*!
    \fn FPrefGeneral::cambioSobreEstilo( const QString &estilo )
 */
void FPrefGeneral::cambioSobreEstilo( const QString &estilo )
{
	QDir dir( QCoreApplication::applicationDirPath() );
	dir.cd( "estilos" );
	dir.cd( estilo );
	QFile file( dir.absoluteFilePath( QString( estilo ).append( ".qss" ) ) );
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	qApp->setStyleSheet(styleSheet);
}
