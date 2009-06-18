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
#include "formservicio.h"

#include <QDate>

#include "eactcerrar.h"
#include "eactguardar.h"
#include "mrecargos.h"
#include "edrecargos.h"

FormServicio::FormServicio ( QWidget* parent, Qt::WFlags fl )
: EVentana( parent, fl ), Ui::FormServicioBase()
{
	setupUi ( this );
	this->setWindowTitle( "Agregar nuevo servicio" );
	this->setWindowIcon( QIcon( ":/imagenes/servicio.png" ) );

	// Pongo la fecha de alta en hoy
	DEFechaAlta->setDate( QDate::currentDate() );

	// Imagenes para los botones de recargos
	PBAgregarRecargo->setIcon( QIcon( ":/imagenes/add.png" ) );
	connect( PBAgregarRecargo, SIGNAL( clicked() ), this, SLOT( agregarRecargo() ) );
	PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
	connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminarRecargo() ) );

	// Dias en el mes que se hace el batch de calcular los nuevos importes 1->31 ( cuidado con los meses  28 y 30 )
	for( int i=1; i<=31; i++ )
	{ CBInicioCobro->addItem( QString::number( i ), QString::number( i ) ); }

	CBMetodoIncompleto->insertItem( -1, "Division por dias y cobro de dias restantes" );

	// Modelo de recargos
	modRecargos = new MRecargos( this );
	TVRecargos->setModel( modRecargos );
	//TVRecargos->hideColumn( 0 );
	//TVRecargos->hideColumn( 1 );
	//TVRecargos->setItemDelegate( new EDRecargos( TVRecargos ) );
	//modRecargos->ponerEnTemporal();
	//modRecargos->select();

	EActGuardar *ActGuardar = new EActGuardar( this );
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );
	addAction( ActGuardar );

	EActCerrar *ActCerrar = new EActCerrar( this );
	connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );
	addAction( ActCerrar );

	connect( dSBPrecioBase, SIGNAL( valueChanged( double ) ), modRecargos, SLOT( setearPrecioBase( double ) ) );
}

FormServicio::~FormServicio()
{
}


/*!
    \fn FormServicio::guardar()
 */
void FormServicio::guardar()
{
 //Verificacion de si los campos son vacios
 if( LENombre->text().isEmpty() )
 { return; }
 if( !DEFechaAlta->date().isValid() )
 { return; }
 if( dSBPrecioBase->value() <= 0 )
 { return; }

}


/*!
    \fn FormServicio:: agregarRecargo()
 */
void FormServicio:: agregarRecargo()
{
 modRecargos->agregarTemporal();
}
