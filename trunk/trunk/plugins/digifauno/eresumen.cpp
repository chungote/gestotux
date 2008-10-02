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
#include "eresumen.h"
#include "resumengeneral.h"
#include "preferencias.h"
#include "evisorinformes.h"

#include <QPushButton>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QGroupBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <algorithm>
#include <QLabel>

EResumen::EResumen( QWidget *parent, tipo que )
: EVentana( parent )
{
 setObjectName( "selectorResumen" );
 setWindowTitle( "Seleccione el Resumen" );
 setAttribute( Qt::WA_DeleteOnClose );
 generar = que;
 QVBoxLayout *layoutPrincipal = new QVBoxLayout( this );
 layoutPrincipal->setMargin( 3 );
 layoutPrincipal->setSpacing( 3 );
 switch( que )
 {
  case diario:
  {
   QGroupBox *g = new QGroupBox( this );
   g->setTitle( "Elija la fecha del resumen" );
   g->setAlignment( Qt::AlignHCenter );
   g->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
   QVBoxLayout *v = new QVBoxLayout( g );
   CWfecha = new QCalendarWidget( g );
   CWfecha->setGridVisible( false );
   CWfecha->setMaximumDate( QDate::currentDate() );
   CWfecha->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
   v->addWidget( CWfecha );
   g->adjustSize();
   layoutPrincipal->addWidget( g );
   break;
  }
  case mensual:
  {
   QGroupBox *g = new QGroupBox( this );
   g->setTitle( "Elija el mes para el resumen" );
   g->setAlignment( Qt::AlignCenter );
   g->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
   QVBoxLayout *v = new QVBoxLayout( g );
   QHBoxLayout *h1 = new QHBoxLayout( g );
   QLabel *etiqueta = new QLabel( g );
   etiqueta->setTextFormat( Qt::RichText );
   etiqueta->setText( "Mes:" );
   h1->addWidget( etiqueta );
   CBMes = new QComboBox( g );
   QLocale locale;
   for( int i = 0; i<12; i++ )
   {
    CBMes->insertItem( i, locale.monthName( i ) );
   }
   CBMes->setCurrentIndex( QDate::currentDate().month() );
   h1->addWidget( CBMes );
   v->addLayout( h1 );
   layoutPrincipal->addWidget( g );
   break;
  }
  case anual:
  {
   QHBoxLayout *layout = new QHBoxLayout( this );
   QLabel *etiqueta = new QLabel( this );
   etiqueta->setText( QString( "A�o:" ) );
   seleccion = new QSpinBox( this );
   seleccion->setRange( 0, QDate::currentDate().year() );
   seleccion->setSingleStep( 1 );
   seleccion->setValue( QDate::currentDate().year() );
   layout->addWidget( etiqueta );
   layout->addWidget( seleccion );
   layoutPrincipal->addLayout( layout );
   break;
  }
  case semanal:
  {
   QGroupBox *g = new QGroupBox( this );
   g->setTitle( "Elija un dia de la semana para el resumen" );
   g->setAlignment( Qt::AlignHCenter );
   g->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
   QVBoxLayout *v = new QVBoxLayout( g );
   CWfecha = new QCalendarWidget( g );
   CWfecha->setGridVisible( true );
   CWfecha->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
   v->addWidget( CWfecha );
   g->adjustSize();
   layoutPrincipal->addWidget( g );
   break;
  }
 }
 QHBoxLayout *layoutBotones = new QHBoxLayout( this );
 layoutBotones->addItem( new QSpacerItem( 10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding ) );
 QPushButton *PBGenerar = new QPushButton( this );
 PBGenerar->setText(  "Generar Reporte" );
 PBGenerar->setIcon( QIcon( ":/imagenes/reporte.png" ) );
 connect( PBGenerar, SIGNAL( clicked() ), this, SLOT( generarResumen() ) );
 layoutBotones->addWidget( PBGenerar );
 QPushButton *PBCancelar = new QPushButton( this );
 PBCancelar->setText( "Cancelar" );
 PBCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( close() ) );
 layoutBotones->addWidget( PBCancelar );
 layoutPrincipal->addLayout( layoutBotones );
 this->adjustSize();
}


EResumen::~EResumen()
{
}




/*!
    \fn EResumen::generarResumen()
	Dependiendo del valor de "tipo" llama a los metodos necesarios para generar el resumen
 */
void EResumen::generarResumen()
{
 QDate primero, ultimo;
 resumenGeneral *resumen = new resumenGeneral( this );
 switch( generar )
 {
  case diario:
  {
   primero = CWfecha->selectedDate();
   ultimo = CWfecha->selectedDate();
   resumen->setTitulo( QString( "Resumen para el dia %1" ).arg( primero.toString() ) );
   resumen->setDescripcion( QString( "Resumen de entradas, salidas y gastos para el dia %1" ).arg( primero.toString() ) );
   resumen->renderizar( primero, ultimo );
   break;
  }
  case mensual:
  {
   resumen->setTitulo( QString( "Resumen para el mes de %1 del a�o %2" ).arg( CBMes->currentText() ).arg( QDate::currentDate().year() ) );
   resumen->setDescripcion( QString( "Resumen detallado de entradas,salidas y gastos para el mes de %1 de %2" ).arg( CBMes->currentText() ).arg( QDate::currentDate().year() ) );
   primero.setDate( QDate::currentDate().year(), CBMes->currentIndex(), 1 );
   ultimo.setDate( QDate::currentDate().year(),  CBMes->currentIndex(), primero.daysInMonth() );
   resumen->renderizar( primero, ultimo );
   break;
  }
  case anual:
  {
   resumen->setTitulo( QString( "Resumen del a�o %1" ).arg( seleccion->value() ) );
   resumen->setDescripcion( QString( "Resumen detallado de entradas,salidas y gastos para el a�o %1" ).arg( seleccion->value() ) );
   primero.setDate( seleccion->value(), 1, 1 );
   ultimo.setDate( seleccion->value(), 12, 31 );
   resumen->renderizar( primero, ultimo );
   break;
  }
  case semanal:
  {
   ultimo = CWfecha->selectedDate().addDays( 7 - CWfecha->selectedDate().dayOfWeek() );
   primero.setDate( CWfecha->selectedDate().year(), CWfecha->selectedDate().month(), CWfecha->selectedDate().day() - CWfecha->selectedDate().dayOfWeek() );
   resumen->setTitulo( "Resumen Semanal" );
   resumen->setDescripcion( QString( "Resumen detallado de entradas, salidas y gastos desde %1 al %2" ).arg( primero.toString() ).arg( ultimo.toString() ) );
   resumen->renderizar( primero, ultimo );
  }
  default:
  {
   //qDebug( "No se especifico que tipo de resumen hacer" );
  }
 }
 EVisorInformes *visor = new EVisorInformes( new QPrinter(), this );
 connect( visor, SIGNAL( paintRequested( QPrinter* ) ), resumen, SLOT( imprimir( QPrinter * ) ) );
 this->agregarVentana( visor );
 close();
}
