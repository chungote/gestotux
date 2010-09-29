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
#include "mmovimientoscaja.h"
#include "mcajas.h"
#include <QGridLayout>
#include <QHeaderView>

VResumenCaja::VResumenCaja( QWidget *parent )
: EVLista( parent )
{
  this->setObjectName( "resumenCaja" );
  this->setWindowTitle( "Resumen de caja" );
  this->setWindowIcon( QIcon( ":/imagenes/caja.png" ) );

  // Inicializo el modelo de la vista
  modelo = new MMovimientosCaja( this );
  vista->setModel( modelo );
  vista->hideColumn( 1 );
  vista->hideColumn( 0 );
  vista->hideColumn( modelo->fieldIndex( "cierre" )) ;
  vista->horizontalHeader()->resizeSections( QHeaderView::ResizeToContents );
  CBCajas = new QComboBox( this );
  // Reordena los items para que el combo box este arriba
  QGridLayout *l = qobject_cast<QGridLayout *>(this->layout());
  QLayoutItem *i = l->takeAt( 0 );
  l->addWidget( CBCajas, 0, 0 );
  l->addItem( i, 1, 0 );

  // Inicializo el modelo de las cajas, lo pongo en el combobox y conecto las señales para cambiar los datos
  cmodelo = new MCajas( CBCajas );
  CBCajas->setModel( cmodelo );
  CBCajas->setModelColumn( 1 );
  connect( CBCajas, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCaja( int ) ) );
  cmodelo->select();

  this->addAction( ActCerrar );
}


void VResumenCaja::cambioCaja( int id )
{
    int id_caja = CBCajas->model()->data( CBCajas->model()->index( id, 0 ), Qt::EditRole ).toInt();
    modelo->ultimosMovimientosCaja( id_caja );
}