/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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

#include "VResumenCaja.h"

#include <QIcon>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QGroupBox>
#include <QLabel>
#include <QDateEdit>

#include "mmovimientoscaja.h"
#include "mcajas.h"
#include "actingresocaja.h"
#include "actretirocaja.h"
#include "acttransferir.h"
#include "FormRetiroIngreso.h"
#include "formtransferir.h"

#include "EReporte.h"

VResumenCaja::VResumenCaja( QWidget *parent )
: EVLista( parent )
{
  this->setObjectName( "resumenCaja" );
  this->setWindowTitle( "Resumen de caja" );
  this->setWindowIcon( QIcon( ":/imagenes/cajaresumen.png" ) );

  // Inicializo el modelo de la vista
  modelo = new MMovimientosCaja( this );
  vista->setModel( modelo );
  vista->hideColumn( 1 );
  vista->hideColumn( 0 );
  vista->hideColumn( modelo->fieldIndex( "cierre" ) );
  vista->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
  vista->horizontalHeader()->setResizeMode( 5, QHeaderView::Stretch );
  vista->horizontalHeader()->setMinimumSectionSize( 60 );
  CBCajas = new QComboBox( this );
  // Reordena los items para que el combo box este arriba
  QGridLayout *l = qobject_cast<QGridLayout *>(this->layout());
  QLayoutItem *i = l->takeAt( 0 );
  l->addWidget( CBCajas, 0, 0 );
  l->addItem( i, 1, 0 );

  // Genero los items para el filtrado
  GBFiltrado = new QGroupBox( this );
  GBFiltrado->setTitle( "Filtrar movimientos de caja" );
  QGridLayout *lg = new QGridLayout();
  GBFiltrado->setLayout( lg );

  QLabel *linicio = new QLabel( GBFiltrado );
  QLabel *lfin = new QLabel( GBFiltrado );
  linicio->setText( "Desde:" );
  lfin->setText( " Hasta: " );

  DTEFin = new QDateEdit( GBFiltrado );
  DTEFin->setMaximumDate( QDate::currentDate() );
  DTEFin->setDate( QDate::currentDate() );

  DTEInicio = new QDateEdit( GBFiltrado );
  DTEInicio->setMaximumDate( QDate::currentDate().addDays( -1 ) );
  /// @todo Buscar fecha del ultimo movimiento
  /*fecha = MMovimientosCaja::buscarUltimoCierre( id_caja );
  DTEInicio->setDate( fecha );*/
  connect( DTEFin, SIGNAL( dateChanged( QDate ) ), this, SLOT( actualizarFiltro() ) );
  connect( DTEInicio, SIGNAL( dateChanged( QDate ) ), this, SLOT( actualizarFiltro() ) );

  lg->addWidget( linicio, 0, 0 );
  lg->addWidget( DTEInicio, 0, 1 );
  lg->addWidget( lfin, 0, 2 );
  lg->addWidget( DTEFin, 0, 3 );
  GBFiltrado->setVisible( false );
  l->addWidget( GBFiltrado, 2, 0 );

  // Inicializo el modelo de las cajas, lo pongo en el combobox y conecto las señales para cambiar los datos
  cmodelo = new MCajas( CBCajas );
  CBCajas->setModel( cmodelo );
  CBCajas->setModelColumn( 1 );
  connect( CBCajas, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCaja( int ) ) );
  cmodelo->select();

  this->vista->horizontalHeader()->resizeSections( QHeaderView::ResizeToContents );

  ActFiltrar = new QAction( this );
  ActFiltrar->setText( "Filtrar" );
  ActFiltrar->setCheckable( true );
  ActFiltrar->setIcon( QIcon( ":/imagenes/buscar.png" ) );
  connect( ActFiltrar, SIGNAL( triggered() ), this, SLOT( filtrar() ) );

  QAction *ActSep = new QAction( this );
  ActSep->setSeparator( true );

  QAction *ActSep2 = new QAction( this );
  ActSep2->setSeparator( true );

  this->addAction( new ActIngresoCaja( this ) );
  this->addAction( new ActRetiroCaja( this ) );
  if( cmodelo->rowCount() > 1 ) {
    this->addAction( new ActTransferir( this ) );
  } else {
      CBCajas->setCurrentIndex( 1 );
      CBCajas->setEnabled( false );
  }
  this->addAction( ActSep );
  this->addAction( ActImprimir );
  this->addAction( ActPdf );
  this->addAction( ActCerrar );
  this->addAction( ActSep2 );
  this->addAction( ActFiltrar );
}


void VResumenCaja::cambioCaja( int id )
{
    int id_caja = CBCajas->model()->data( CBCajas->model()->index( id, 0 ), Qt::EditRole ).toInt();
    modelo->ultimosMovimientosCaja( id_caja );
}

void VResumenCaja::ingreso() {
    FormRetiroIngreso *f = new FormRetiroIngreso( this, FormRetiroIngreso::Ingreso );
    f->setearCaja( CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt() );
    f->exec();
    modelo->ultimosMovimientosCaja( CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt() );
}

void VResumenCaja::retiro() {
    FormRetiroIngreso *f = new FormRetiroIngreso( this, FormRetiroIngreso::Retiro );
    f->setearCaja( CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt() );
    f->exec();
    modelo->ultimosMovimientosCaja( CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt() );
}

void VResumenCaja::transferir() {
    int id_caja = CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt();
    FormTransferir *ft = new FormTransferir();
    ft->setearCajaOrigen( id_caja );
    ft->exec();
}

void VResumenCaja::imprimir()
{
    EReporte *rep = new EReporte( 0 );

    ParameterList parametros;
    parametros.append( "id_caja", CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt() );
    if( ActFiltrar->isChecked() ) {
        parametros.append( "filtro", this->modelo->filter() );
    }
    rep->especial( "ResumenCaja", parametros );
    rep->hacer();

    delete rep;
}

void VResumenCaja::aPdf()
{
    EReporte *rep = new EReporte( 0 );

    ParameterList parametros;
    parametros.append( "id_caja", CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt() );
    if( ActFiltrar->isChecked() ) {
        parametros.append( "filtro", this->modelo->filter() );
    }
    rep->especial( "ResumenCaja", parametros );
    rep->hacerPDF( parametros, "Resumen de caja " + CBCajas->currentText() );

    delete rep;
}

void VResumenCaja::filtrar()
{
    if( ActFiltrar->isChecked() ) {
        GBFiltrado->setVisible( true );
    } else {
        GBFiltrado->setVisible( false );
        this->modelo->setFilter( "" );
    }
}

void VResumenCaja::actualizarFiltro()
{
    this->modelo->setFilter( QString( " fecha_hora >= date( '%1' ) AND fecha_hora <= date( '%2' ) AND id_caja = %3" )
                             .arg( DTEInicio->date().toString( "yyyy-MM-dd" ) )
                             .arg( DTEFin->date().toString( "yyyy-MM-dd" ) )
                             .arg( CBCajas->model()->data( CBCajas->model()->index( CBCajas->currentIndex(), 0 ), Qt::EditRole ).toInt() ) );
    this->modelo->select();
    //qDebug( this->modelo->filter().toLocal8Bit() );
}
