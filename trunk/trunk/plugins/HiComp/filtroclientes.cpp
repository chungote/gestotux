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
#include <QSqlQueryModel>
#include <QComboBox>

#include "filtroclientes.h"

FiltroClientes::FiltroClientes(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::FiltroClientesBase()
{
	setupUi(this);
	this->setAttribute( Qt::WA_DeleteOnClose );
	QSqlQueryModel *modelo = new QSqlQueryModel( this );
	modelo->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );
	
	CBClientes->setModel( modelo );
	CBClientes->setModelColumn( 1 );
	CBClientes->setEditable( false );

	GBfiltrar->setChecked( false );
	CBClientes->setCurrentIndex( -1 );

	connect( GBfiltrar, SIGNAL( toggled( bool ) ), this, SLOT( seteaFiltradoSlot( bool ) ) );
	connect( CBClientes, SIGNAL( currentIndexChanged ( int ) ), this, SLOT( cambioClienteSlot( int ) ) );
}

FiltroClientes::~FiltroClientes()
{
}




/*!
    \fn FiltroClientes::cambioClienteSlot( int idcombo )
 */
void FiltroClientes::cambioClienteSlot( int idcombo )
{
  emit cambioCliente( CBClientes->model()->data( CBClientes->model()->index( CBClientes->currentIndex(), 0 ), Qt::EditRole  ).toInt() );
}


/*!
    \fn FiltroClientes::seteaFiltradoSlot( bool activo )
 */
void FiltroClientes::seteaFiltradoSlot( bool activo )
{
 emit seteaFiltrado( activo, CBClientes->model()->data( CBClientes->model()->index( CBClientes->currentIndex(), 0 ), Qt::EditRole  ).toInt() );
}
